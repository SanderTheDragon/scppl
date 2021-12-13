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

// Single type
constexpr uint8_t  A = 0x01;
constexpr uint16_t B = 0x01'23;
constexpr uint32_t C = 0x01'23'45'67;
constexpr uint64_t D = 0x01'23'45'67'89'AB'CD'EF;

constexpr ByteArray<sizeof(A)> ADataLE{'\x01'};
constexpr ByteArray<sizeof(B)> BDataLE{'\x23', '\x01'};
constexpr ByteArray<sizeof(C)> CDataLE{'\x67', '\x45', '\x23', '\x01'};
constexpr ByteArray<sizeof(D)> DDataLE{'\xEF', '\xCD', '\xAB', '\x89',
                                       '\x67', '\x45', '\x23', '\x01'};

constexpr ByteArray<sizeof(A)> ADataBE{'\x01'};
constexpr ByteArray<sizeof(B)> BDataBE{'\x01', '\x23'};
constexpr ByteArray<sizeof(C)> CDataBE{'\x01', '\x23', '\x45', '\x67'};
constexpr ByteArray<sizeof(D)> DDataBE{'\x01', '\x23', '\x45', '\x67',
                                       '\x89', '\xAB', '\xCD', '\xEF'};

// Array
constexpr std::array<std::remove_cvref_t<decltype(A)>, 1> AArray{A};
constexpr std::array<std::remove_cvref_t<decltype(B)>, 2> BArray{B, B};
constexpr std::array<std::remove_cvref_t<decltype(C)>, 3> CArray{C, C, C};
constexpr std::array<std::remove_cvref_t<decltype(D)>, 4> DArray{D, D, D, D};

constexpr ByteArray<sizeof(AArray)> AArrayDataLE = combineArrays(ADataLE);
constexpr ByteArray<sizeof(BArray)> BArrayDataLE = combineArrays(BDataLE,
                                                                 BDataLE);
constexpr ByteArray<sizeof(CArray)> CArrayDataLE = combineArrays(CDataLE,
                                                                 CDataLE,
                                                                 CDataLE);
constexpr ByteArray<sizeof(DArray)> DArrayDataLE = combineArrays(DDataLE,
                                                                 DDataLE,
                                                                 DDataLE,
                                                                 DDataLE);

constexpr ByteArray<sizeof(AArray)> AArrayDataBE = combineArrays(ADataBE);
constexpr ByteArray<sizeof(BArray)> BArrayDataBE = combineArrays(BDataBE,
                                                                 BDataBE);
constexpr ByteArray<sizeof(CArray)> CArrayDataBE = combineArrays(CDataBE,
                                                                 CDataBE,
                                                                 CDataBE);
constexpr ByteArray<sizeof(DArray)> DArrayDataBE = combineArrays(DDataBE,
                                                                 DDataBE,
                                                                 DDataBE,
                                                                 DDataBE);

// Struct of two types
#pragma pack(push, 1)
struct AB_t
{
    std::remove_cvref_t<decltype(A)> a{A};
    std::remove_cvref_t<decltype(B)> b{B};
};

inline auto operator==(AB_t lhs, AB_t rhs)
    -> bool
{
    return (lhs.a == rhs.a && lhs.b == rhs.b);
}

struct CD_t
{
    std::remove_cvref_t<decltype(C)> c{C};
    std::remove_cvref_t<decltype(D)> d{D};
};

inline auto operator==(CD_t lhs, CD_t rhs)
    -> bool
{
    return (lhs.c == rhs.c && lhs.d == rhs.d);
}
#pragma pack(pop)

constexpr AB_t AB{};
constexpr CD_t CD{};

constexpr ByteArray<sizeof(AB)> ABDataLE = combineArrays(ADataLE, BDataLE);
constexpr ByteArray<sizeof(CD)> CDDataLE = combineArrays(CDataLE, DDataLE);

constexpr ByteArray<sizeof(AB)> ABDataBE = combineArrays(ADataBE, BDataBE);
constexpr ByteArray<sizeof(CD)> CDDataBE = combineArrays(CDataBE, DDataBE);

// Struct of arrays
#pragma pack(push, 1)
struct ABCDArray_t
{
    std::remove_cvref_t<decltype(AArray)> a{AArray};
    std::remove_cvref_t<decltype(BArray)> b{BArray};
    std::remove_cvref_t<decltype(CArray)> c{CArray};
    std::remove_cvref_t<decltype(DArray)> d{DArray};
};

inline auto operator==(ABCDArray_t lhs, ABCDArray_t rhs)
    -> bool
{
    return (lhs.a == rhs.a && lhs.b == rhs.b &&
            lhs.c == rhs.c && lhs.d == rhs.d);
}
#pragma pack(pop)

constexpr ABCDArray_t ABCDArray{};

constexpr ByteArray<sizeof(ABCDArray)> ABCDArrayDataLE =
    combineArrays(AArrayDataLE, BArrayDataLE, CArrayDataLE, DArrayDataLE);
constexpr ByteArray<sizeof(ABCDArray)> ABCDArrayDataBE =
    combineArrays(AArrayDataBE, BArrayDataBE, CArrayDataBE, DArrayDataBE);

// Struct of struct of single type
#pragma pack(push, 1)
struct AB_CD_t
{
    std::remove_cvref_t<decltype(AB)> ab{AB};
    std::remove_cvref_t<decltype(CD)> cd{CD};
};

inline auto operator==(AB_CD_t lhs, AB_CD_t rhs)
    -> bool
{
    return (lhs.ab == rhs.ab && lhs.cd == rhs.cd);
}
#pragma pack(pop)

constexpr AB_CD_t AB_CD{};

constexpr ByteArray<sizeof(AB_CD)> AB_CDDataLE = combineArrays(ABDataLE,
                                                               CDDataLE);

constexpr ByteArray<sizeof(AB_CD)> AB_CDDataBE = combineArrays(ABDataBE,
                                                               CDDataBE);

#endif
