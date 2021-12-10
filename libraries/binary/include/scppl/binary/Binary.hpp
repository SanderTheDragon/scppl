// SPDX-FileCopyrightText: 2021 SanderTheDragon <sanderthedragon@zoho.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef SCPPL_BINARY_BINARY_HPP_
#define SCPPL_BINARY_BINARY_HPP_

#include <algorithm>
#include <bit>
#include <cstring>
#include <ranges>
#include <tuple>

#ifdef SCPPL_CONFING_BINARY_USE_PFR
#include <boost/pfr.hpp>
#endif

#include "scppl/binary/Concepts.hpp"

namespace scppl {

/**
 * @brief Calculate the total length of a parameter pack.
 *
 * @details Calculates the total length of parameter pack `Ts` by calculating
 *          the sum of each `sizeof(T)` for `T` in `Ts...` using a fold
 *          expression.
 *
 * @tparam Ts  The types to get the length of.
 *
 * @return The total length of the parameter pack.
 */
template<typename... Ts>
constexpr auto lengthOf()
    -> std::size_t
{
    return (sizeof(Ts) + ...);
}

/**
 * @brief Pack and unpack binary data.
 */
class Binary
{
    using Byte = char;

    template<std::size_t N>
    using ByteArray = std::array<Byte, N>;

public:
    /**
     * @brief Pack `values` of types `Ts...` into raw data.
     *
     * @sa scppl::Binary::toBytes()
     *
     * @tparam tEndian  The endian of the data.
     * @tparam Ts       The types to pack.
     *
     * @param values  The values of types `Ts...` to pack.
     *
     * @return An array containing raw data.
     */
    template<std::endian tEndian = std::endian::native, Packable... Ts>
    static auto pack(Ts... values)
        -> ByteArray<lengthOf<Ts...>()>
    {
        ByteArray<lengthOf<Ts...>()> data{};
        auto position = std::ranges::begin(data); // NOLINT
        auto packValue = [&]<typename T>(T value) -> void
        {
            auto raw = Binary::toBytes<tEndian, T>(value);
            position = std::ranges::copy_n(std::ranges::begin(raw), sizeof(T),
                                           position).out;
        };

        (packValue.template operator()<Ts>(values), ...);

        return data;
    }

    /**
     * @brief Unpack raw bytes into values of types `Ts...`.
     *
     * @sa scppl::Binary::fromBytes()
     *
     * @tparam tEndian  The endian of the data.
     * @tparam Ts       The types of values to unpack.
     *
     * @param data  A range containing the raw data to unpack from.
     *
     * @return A tuple containing the unpacked values.
     */
    template<std::endian tEndian = std::endian::native, Unpackable... Ts>
    static auto unpack(RangeOf<Byte> auto data)
        -> std::tuple<Ts...>
    {
        auto position = std::ranges::begin(data);
        auto unpackValue = [&]<typename T>() -> T
        {
            std::array<Byte, sizeof(T)> value{};
            position = std::ranges::copy_n(position, sizeof(T),
                                           std::ranges::begin(value)).in;

            return Binary::fromBytes<tEndian, T>(value);
        };

        return std::tuple<Ts...>{unpackValue.template operator()<Ts>()...};
    }

    /**
     * @brief Converts a single value of type `T` into raw bytes.
     *
     * @tparam tEndian  The endian of the data.
     * @tparam T        The type of the value to convert.
     *
     * @param value  The value of type `T` to convert.
     *
     * @return An array containing the binary data.
     */
    template<std::endian tEndian = std::endian::native, Packable T>
#ifdef SCPPL_CONFING_BINARY_USE_PFR
    requires(!std::ranges::range<T> &&
             (!std::is_class_v<T> || tEndian == std::endian::native))
#else
    requires(!std::ranges::range<T>)
#endif
    static auto toBytes(T value)
        -> ByteArray<sizeof(T)>
    {
        ByteArray<sizeof(T)> raw{};
        std::memcpy(std::ranges::data(raw), &value, sizeof(T));

        if constexpr(std::is_scalar_v<T> && tEndian != std::endian::native)
            std::ranges::reverse(raw);

        return raw;
    }

    /**
     * @brief Converts a range of type `T` into raw bytes.
     *
     * @tparam tEndian  The endian of the data.
     * @tparam T        The type of range to convert.
     *
     * @param value  The range of type `T` to convert.
     *
     * @return An array containing the binary data.
     */
    template<std::endian tEndian = std::endian::native, Packable T>
    requires(std::ranges::sized_range<T>)
    static auto toBytes(T range)
        -> ByteArray<sizeof(T)>
    {
        using RangeT = std::ranges::range_value_t<T>;

        ByteArray<sizeof(T)> raw{};
        auto position = std::ranges::begin(raw);
        for (std::size_t i = 0; i < std::ranges::size(range); ++i)
        {
            ByteArray<sizeof(RangeT)> itemBytes =
                Binary::toBytes<tEndian, RangeT>(range.at(i));

            position = std::ranges::copy(std::ranges::begin(itemBytes),
                                         std::ranges::end(itemBytes),
                                         position).out;
        }

        return raw;
    }

#ifdef SCPPL_CONFING_BINARY_USE_PFR
    /**
     * @brief Converts all fields of struct `T` into raw bytes.
     *
     * @tparam tEndian  The endian of the data.
     * @tparam T        The type of the value to convert.
     *
     * @param value  The value of struct `T` to convert.
     *
     * @return An array containing the binary data.
     */
    template<std::endian tEndian = std::endian::native, Packable T>
    requires(!std::ranges::range<T> &&
             (std::is_class_v<T> && tEndian != std::endian::native))
    static auto toBytes(T value)
        -> ByteArray<sizeof(T)>
    {
        ByteArray<sizeof(T)> raw{};
        auto position = std::ranges::begin(raw);
        auto convertField = [&]<typename FieldT>(FieldT field) -> void
        {
            static_assert(Packable<FieldT>, "`FieldT` is not `Packable`");

            auto fieldBytes = Binary::toBytes<tEndian, FieldT>(field);
            position = std::ranges::copy(std::ranges::begin(fieldBytes),
                                         std::ranges::end(fieldBytes),
                                         position).out;
        };

        boost::pfr::for_each_field(value, convertField);

        return raw;
    }
#endif

    /**
     * @brief Converts raw bytes into a single value of type `T`.
     *
     * @tparam tEndian  The endian of the data.
     * @tparam T        The type of the value to convert.
     *
     * @param raw  The binary data to convert into type `T`.
     *
     * @return The value of type `T`.
     */
    template<std::endian tEndian = std::endian::native, Unpackable T>
#ifdef SCPPL_CONFING_BINARY_USE_PFR
    requires(!std::ranges::range<T> &&
             (!std::is_class_v<T> || tEndian == std::endian::native))
#else
    requires(!std::ranges::range<T>)
#endif
    static auto fromBytes(RangeOf<Byte> auto raw)
        -> T
    {
        if constexpr(std::is_scalar_v<T> && tEndian != std::endian::native)
            std::ranges::reverse(raw);

        T value{};
        std::memcpy(&value, std::ranges::data(raw), sizeof(T));

        return value;
    }

    /**
     * @brief Converts raw bytes into a range of type `T`.
     *
     * @tparam tEndian  The endian of the data.
     * @tparam T        The type of the range to convert.
     *
     * @param raw  The binary data to convert into the range.
     *
     * @return The range of type `T`.
     */
    template<std::endian tEndian = std::endian::native, Unpackable T>
    requires(std::ranges::sized_range<T>)
    static auto fromBytes(RangeOf<Byte> auto raw)
        -> T
    {
        using RangeT = std::ranges::range_value_t<T>;

        T range{};
        auto position = std::ranges::begin(raw);
        for (std::size_t i = 0; i < std::ranges::size(range); ++i)
        {
            ByteArray<sizeof(RangeT)> itemBytes{};
            position = std::ranges::copy_n(position, sizeof(RangeT),
                                           std::ranges::begin(itemBytes)).in;

            range.at(i) = Binary::fromBytes<tEndian, RangeT>(itemBytes);
        }

        return range;
    }

#ifdef SCPPL_CONFING_BINARY_USE_PFR
    /**
     * @brief Converts raw bytes into a struct of type `T`.
     *
     * @tparam tEndian  The endian of the data.
     * @tparam T        The type of the value to convert.
     *
     * @param raw  The binary data to convert into struct `T`.
     *
     * @return The value of struct `T`.
     */
    template<std::endian tEndian = std::endian::native, Unpackable T>
    requires(!std::ranges::range<T> &&
             (std::is_class_v<T> && tEndian != std::endian::native))
    static auto fromBytes(RangeOf<Byte> auto raw)
        -> T
    {
        auto position = std::ranges::begin(raw);
        auto convertField = [&]<typename FieldT>(FieldT& field) -> void
        {
            static_assert(Unpackable<FieldT>, "`FieldT` is not `Unpackable`");

            ByteArray<sizeof(FieldT)> fieldBytes{};
            position = std::ranges::copy_n(position, sizeof(FieldT),
                                           std::ranges::begin(fieldBytes)).in;

            field = Binary::fromBytes<tEndian, FieldT>(fieldBytes);
        };

        T value{};

        boost::pfr::for_each_field(value, convertField);

        return value;
    }
#endif
};

}

#endif
