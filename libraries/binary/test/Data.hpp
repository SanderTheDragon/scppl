// SPDX-FileCopyrightText: 2021 SanderTheDragon <sanderthedragon@zoho.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef TEST_DATA_HPP_
#define TEST_DATA_HPP_

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

constexpr uint8_t  A = 0x01;
constexpr uint16_t B = 0x01'23;
constexpr uint32_t C = 0x01'23'45'67;
constexpr uint64_t D = 0x01'23'45'67'89'AB'CD'EF;

constexpr std::array<char, sizeof(A)> AData{'\x01'};
constexpr std::array<char, sizeof(B)> BData{'\x23', '\x01'};
constexpr std::array<char, sizeof(C)> CData{'\x67', '\x45', '\x23', '\x01'};
constexpr std::array<char, sizeof(D)> DData{'\xEF', '\xCD', '\xAB', '\x89',
                                            '\x67', '\x45', '\x23', '\x01'};

#pragma pack(push, 1)
struct AB_t
{
    decltype(A) a{A};
    decltype(B) b{B};
};

inline auto operator==(AB_t lhs, AB_t rhs)
    -> bool
{
    return (lhs.a == rhs.a && lhs.b == rhs.b);
}

struct CD_t
{
    decltype(C) c{C};
    decltype(D) d{D};
};

inline auto operator==(CD_t lhs, CD_t rhs)
    -> bool
{
    return (lhs.c == rhs.c && lhs.d == rhs.d);
}

struct AB_CD_t
{
    AB_t ab{};
    CD_t cd{};
};

inline auto operator==(AB_CD_t lhs, AB_CD_t rhs)
    -> bool
{
    return (lhs.ab == rhs.ab && lhs.cd == rhs.cd);
}
#pragma pack(pop)

template<std::size_t... Ns>
constexpr auto combineArray(std::array<char, Ns>... arrays)
    -> std::array<char, (Ns + ...)>
{
    std::array<char, (Ns + ...)> result{};
    auto position = std::ranges::begin(result); // NOLINT
    auto append = [&]<std::size_t N>(std::array<char, N> array) -> void
    {
        position =
            std::ranges::copy_n(std::ranges::begin(array), N, position).out;
    };

    (append.template operator()<Ns>(arrays), ...);

    return result;
}

constexpr AB_t AB{};
constexpr CD_t CD{};
constexpr AB_CD_t AB_CD{};

constexpr std::array<char, sizeof(AB)> ABData = combineArray(AData, BData);
constexpr std::array<char, sizeof(CD)> CDData = combineArray(CData, DData);
constexpr std::array<char, sizeof(AB_CD)> AB_CDData = combineArray(ABData,
                                                                   CDData);

#endif
