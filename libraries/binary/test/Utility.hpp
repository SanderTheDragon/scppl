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

// NOLINTBEGIN(cppcoreguidelines-macro-usage): Macros required here
#define PARENTHESES ()

#define EXPAND(...) EXPAND_HELPER(EXPAND_HELPER(EXPAND_HELPER(__VA_ARGS__)))
#define EXPAND_HELPER(...) EXPAND_HELPER_HELPER(__VA_ARGS__)
#define EXPAND_HELPER_HELPER(...) __VA_ARGS__

#define FOR_EACH(macro, ...) \
    __VA_OPT__(EXPAND(FOR_EACH_HELPER(macro, __VA_ARGS__)))
#define FOR_EACH_HELPER(macro, first, ...) \
    macro(first) \
    __VA_OPT__(, FOR_EACH_AGAIN PARENTHESES (macro, __VA_ARGS__))
#define FOR_EACH_AGAIN() FOR_EACH_HELPER

#define DATA_NAME_LE(variable) variable ## DataLE
#define DATA_NAME_BE(variable) variable ## DataBE

#define TYPE_OF(variable) std::remove_const_t<decltype(variable)>
// NOLINTEND(cppcoreguidelines-macro-usage)

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

template<std::size_t... Ns>
auto toStream(ByteArray<Ns>... input)
    -> std::tuple<std::string, std::istringstream>
{
    auto data = combineArrays(input...);

    std::string string{};
    string.resize((Ns + ...));

    std::ranges::copy(std::ranges::begin(data), std::ranges::end(data),
                      std::ranges::begin(string));

    std::istringstream stream(string);
    stream.seekg(0);

    return { string, std::move(stream) };
}

template<std::size_t N>
auto fromStream(std::ostringstream const& stream)
    -> ByteArray<N>
{
    auto string = stream.str();
    ByteArray<N> data{};
    std::ranges::copy(std::ranges::begin(string), std::ranges::end(string),
                      std::ranges::begin(data));

    return data;
}

#endif
