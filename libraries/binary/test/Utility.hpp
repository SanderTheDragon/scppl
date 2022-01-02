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

// NOLINTBEGIN: Macros required here
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
// NOLINTEND

template<std::size_t N>
using ByteArray = std::array<char, N>;

template<std::size_t... Ns>
constexpr auto combineArrays(ByteArray<Ns>... arrays)
    -> ByteArray<(Ns + ...)>
{
    ByteArray<(Ns + ...)> result{};
    auto position = std::ranges::begin(result); // NOLINT
    auto append = [&]<std::size_t N>(ByteArray<N> array) -> void
    {
        position =
            std::ranges::copy_n(std::ranges::begin(array), N, position).out;
    };

    (append.template operator()<Ns>(arrays), ...);

    return result;
}

#endif
