// SPDX-FileCopyrightText: 2021-2022 SanderTheDragon <sanderthedragon@zoho.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef TEST_UTILITY_HPP_
#define TEST_UTILITY_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <ranges>

#include <gtest/gtest.h>

#include "Types.hpp"

template<std::size_t... Ns>
constexpr auto combineArrays(ByteArray<Ns>... arrays)
    -> ByteArray<(Ns + ...)>
{
    ByteArray<(Ns + ...)> result{};
    auto position = std::ranges::begin(result);
    auto append = [&]<std::size_t N>(ByteArray<N> array) -> void
    {
        position =
            std::ranges::copy_n(std::ranges::begin(array), N, position).out;
    };

    (append.template operator()<Ns>(arrays), ...);

    return result;
}

template<std::size_t I = 0, typename... Ts>
requires(I == sizeof...(Ts))
void assertValuesEqual(std::tuple<Ts...> /* values */,
                       std::tuple<Ts...> /* expected */)
{
    //
}

template<std::size_t I = 0, typename... Ts>
requires(I < sizeof...(Ts))
void assertValuesEqual(std::tuple<Ts...> values,
                       std::tuple<Ts...> expected)
{
    ASSERT_EQ(std::get<I>(values), std::get<I>(expected));

    assertValuesEqual<I + 1>(values, expected);
}

template<std::size_t N>
void assertDataEqual(ByteArray<N> data, ByteArray<N> expected)
{
    for (std::size_t i = 0; i < N; ++i)
        ASSERT_EQ(data.at(i), expected.at(i));
}

template<std::size_t N, std::size_t... Ns>
requires((Ns + ...) == N)
void assertDataEqual(ByteArray<N> data, ByteArray<Ns>... expected)
{
    assertDataEqual(data, combineArrays(expected...));
}

#endif
