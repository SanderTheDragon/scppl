// SPDX-FileCopyrightText: 2021 SanderTheDragon <sanderthedragon@zoho.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef SCPPL_BINARY_BINARY_HPP_
#define SCPPL_BINARY_BINARY_HPP_

#include <algorithm>
#include <cstring>
#include <ranges>
#include <tuple>

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
     * @tparam Ts  The types to pack.
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
            auto raw = Binary::toBytes<T>(value);
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
     * @tparam Ts  The types of values to unpack.
     *
     * @param data  A range containing the raw data to unpack from.
     *
     * @return A tuple containing the unpacked values.
     */
    template<Unpackable... Ts>
    static auto unpack(RangeOf<Byte> auto data)
        -> std::tuple<Ts...>
    {
        auto position = std::ranges::begin(data);
        auto unpackValue = [&]<typename T>() -> T
        {
            std::array<Byte, sizeof(T)> value{};
            position = std::ranges::copy_n(position, sizeof(T),
                                           std::ranges::begin(value)).in;

            return Binary::fromBytes<T>(std::move(value));
        };

        return std::tuple<Ts...>{unpackValue.template operator()<Ts>()...};
    }

    /**
     * @brief Converts a single value of type `T` into raw bytes.
     *
     * @tparam T  The type of the value to convert.
     *
     * @param value  The value of type `T` to convert.
     *
     * @return An array containing the binary data.
     */
    template<Packable T>
    static auto toBytes(T value)
        -> ByteArray<sizeof(T)>
    {
        ByteArray<sizeof(T)> raw{};
        std::memcpy(std::ranges::data(raw), &value, sizeof(T));

        return raw;
    }

    /**
     * @brief Converts raw bytes into a single value of type `T`.
     *
     * @tparam T  The type of the value to convert.
     *
     * @param raw  The binary data to convert into type `T`.
     *
     * @return The value of type `T`.
     */
    template<Unpackable T>
    static auto fromBytes(RangeOf<Byte> auto raw)
        -> T
    {
        T value{};
        std::memcpy(&value, std::ranges::data(raw), sizeof(T));

        return value;
    }
};

}

#endif
