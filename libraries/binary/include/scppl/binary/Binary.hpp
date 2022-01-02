// SPDX-FileCopyrightText: 2021-2022 SanderTheDragon <sanderthedragon@zoho.com>
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
#include "scppl/binary/Utility.hpp"

namespace scppl {

/**
 * @brief Pack and unpack binary data.
 *
 * @tparam tEndian  The endian of the data. [`std::endian::native`]
 * @tparam ByteT    The type to use as a byte. [`char`]
 */
template<std::endian tEndian = std::endian::native, typename ByteT = char>
class Binary
{
public:
    /// The byte type of this `Binary` instance.
    using Byte = ByteT;

    /// A simple alias for an array of `Byte`s.
    template<std::size_t N>
    using ByteArray = std::array<Byte, N>;

    /// The endian of this `Binary` instance.
    static constexpr auto endian() -> std::endian { return tEndian; }

    /**
     * @brief Pack `values` of types `Ts...` into raw data.
     *
     * @sa scppl::Binary::toBytes()
     *
     * @tparam Ts       The types to pack, must be `Packable`.
     *
     * @param values  The values of types `Ts...` to pack.
     *
     * @return An array containing raw data.
     */
    template<Packable... Ts>
    static auto pack(Ts... values)
        -> ByteArray<lengthOf<Ts...>()>
    {
        ByteArray<lengthOf<Ts...>()> data{};
        auto position = std::ranges::begin(data); // NOLINT
        auto packValue = [&]<typename T>(T value) -> void
        {
            auto raw = toBytes<T>(value);
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
     * @tparam Ts       The types of values to unpack, must be `Unpackable`.
     *
     * @param data  A range containing the raw data to unpack from.
     *
     * @return A tuple containing the unpacked values.
     */
    template<Unpackable... Ts>
    static auto unpack(RangeOfEqualSizedType<Byte> auto data)
        -> std::tuple<Ts...>
    {
        auto position = std::ranges::begin(data);
        auto unpackValue = [&]<typename T>() -> T
        {
            std::array<Byte, sizeof(T)> value{};
            position = std::ranges::copy_n(position, sizeof(T),
                                           std::ranges::begin(value)).in;

            return fromBytes<T>(value);
        };

        return std::tuple<Ts...>{unpackValue.template operator()<Ts>()...};
    }

    /**
     * @brief Unpack raw bytes into values of types `Ts...`.
     *
     * @tparam Ts       The types of values to unpack, must be `Unpackable`.
     *
     * @param data    A range containing the raw data to unpack from.
     * @param values  References to the values to unpack into.
     */
    template<Unpackable... Ts>
    static void unpack(RangeOf<Byte> auto data, Ts&... values)
    {
        std::tie(values...) = unpack<Ts...>(data);
    }

    /**
     * @brief Converts a single value of type `T` into raw bytes.
     *
     * @tparam T        The type of the value to convert, must be `Packable`.
     *
     * @param value  The value of type `T` to convert.
     *
     * @return An array containing the binary data.
     */
    template<Packable T>
#ifdef SCPPL_CONFING_BINARY_USE_PFR
    requires(!std::ranges::range<T> &&
             (!std::is_class_v<T> || endian() == std::endian::native))
#else
    requires(!std::ranges::range<T>)
#endif
    static auto toBytes(T value)
        -> ByteArray<sizeof(T)>
    {
        ByteArray<sizeof(T)> raw{};
        std::memcpy(std::ranges::data(raw), &value, sizeof(T));

        if constexpr(std::is_scalar_v<T> && endian() != std::endian::native)
            std::ranges::reverse(raw);

        return raw;
    }

    /**
     * @brief Converts a range of type `T` into raw bytes.
     *
     * @tparam T        The type of range to convert, must be `Packable`.
     *
     * @param range  The range of type `T` to convert.
     *
     * @return An array containing the binary data.
     */
    template<Packable T>
    requires(std::ranges::sized_range<T>)
    static auto toBytes(T range)
        -> ByteArray<sizeof(T)>
    {
        using RangeT = std::ranges::range_value_t<T>;

        ByteArray<sizeof(T)> raw{};
        auto position = std::ranges::begin(raw);
        for (RangeT const& item : range)
        {
            ByteArray<sizeof(RangeT)> itemBytes = toBytes<RangeT>(item);

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
     * @tparam T        The type of the value to convert, must be `Packable`.
     *
     * @param value  The value of struct `T` to convert.
     *
     * @return An array containing the binary data.
     */
    template<Packable T>
    requires(!std::ranges::range<T> &&
             (std::is_class_v<T> && endian() != std::endian::native))
    static auto toBytes(T value)
        -> ByteArray<sizeof(T)>
    {
        ByteArray<sizeof(T)> raw{};
        auto position = std::ranges::begin(raw);
        auto convertField = [&]<typename FieldT>(FieldT field) -> void
        {
            static_assert(Packable<FieldT>, "`FieldT` is not `Packable`");

            auto fieldBytes = toBytes<FieldT>(field);
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
     * @tparam T        The type of the value to convert, must be `Unpackable`.
     *
     * @param raw  The binary data to convert into type `T`.
     *
     * @return The value of type `T`.
     */
    template<Unpackable T>
#ifdef SCPPL_CONFING_BINARY_USE_PFR
    requires(!std::ranges::range<T> &&
             (!std::is_class_v<T> || endian() == std::endian::native))
#else
    requires(!std::ranges::range<T>)
#endif
    static auto fromBytes(RangeOfEqualSizedType<Byte> auto raw)
        -> T
    {
        if constexpr(std::is_scalar_v<T> && endian() != std::endian::native)
            std::ranges::reverse(raw);

        T value{};
        std::memcpy(&value, std::ranges::data(raw), sizeof(T));

        return value;
    }

    /**
     * @brief Converts raw bytes into a range of type `T`.
     *
     * @tparam T        The type of the range to convert, must be `Unpackable`.
     *
     * @param raw  The binary data to convert into the range.
     *
     * @return The range of type `T`.
     */
    template<Unpackable T>
    requires(std::ranges::sized_range<T>)
    static auto fromBytes(RangeOfEqualSizedType<Byte> auto raw)
        -> T
    {
        using RangeT = std::ranges::range_value_t<T>;

        T range{};
        auto position = std::ranges::begin(raw);
        for (RangeT& item : range)
        {
            ByteArray<sizeof(RangeT)> itemBytes{};
            position = std::ranges::copy_n(position, sizeof(RangeT),
                                           std::ranges::begin(itemBytes)).in;

            item = fromBytes<RangeT>(itemBytes);
        }

        return range;
    }

#ifdef SCPPL_CONFING_BINARY_USE_PFR
    /**
     * @brief Converts raw bytes into a struct of type `T`.
     *
     * @tparam T        The type of the value to convert, must be `Unpackable`.
     *
     * @param raw  The binary data to convert into struct `T`.
     *
     * @return The value of struct `T`.
     */
    template<Unpackable T>
    requires(!std::ranges::range<T> &&
             (std::is_class_v<T> && endian() != std::endian::native))
    static auto fromBytes(RangeOfEqualSizedType<Byte> auto raw)
        -> T
    {
        auto position = std::ranges::begin(raw);
        auto convertField = [&]<typename FieldT>(FieldT& field) -> void
        {
            static_assert(Unpackable<FieldT>, "`FieldT` is not `Unpackable`");

            ByteArray<sizeof(FieldT)> fieldBytes{};
            position = std::ranges::copy_n(position, sizeof(FieldT),
                                           std::ranges::begin(fieldBytes)).in;

            field = fromBytes<FieldT>(fieldBytes);
        };

        T value{};
        boost::pfr::for_each_field(value, convertField);

        return value;
    }
#endif
};

}

#endif
