// SPDX-FileCopyrightText: 2021 SanderTheDragon <sanderthedragon@zoho.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef TEST_TYPES_HPP_
#define TEST_TYPES_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <ranges>

#include <gtest/gtest.h>

#include "Utility.hpp"

using A_t = uint8_t;
using B_t = uint16_t;
using C_t = uint32_t;
using D_t = uint64_t;

template<std::size_t N> using AArray_t = std::array<A_t, N>;
template<std::size_t N> using BArray_t = std::array<B_t, N>;
template<std::size_t N> using CArray_t = std::array<C_t, N>;
template<std::size_t N> using DArray_t = std::array<D_t, N>;

#pragma pack(push, 1)
struct AB_t
{
    A_t a{};
    B_t b{};
};

struct CD_t
{
    C_t c{};
    D_t d{};
};

struct AB_CD_t
{
    AB_t ab{};
    CD_t cd{};
};
#pragma pack(pop)

template<std::size_t N> using AB_CDArray_t = std::array<AB_CD_t, N>;

#pragma pack(push, 1)
template<std::size_t Na, std::size_t Nb, std::size_t Nc, std::size_t Nd>
struct ABCDArray_t
{
    AArray_t<Na> a{};
    BArray_t<Nb> b{};
    CArray_t<Nc> c{};
    DArray_t<Nd> d{};
};
#pragma pack(pop)

template<std::size_t N, std::size_t... Ns>
using ABCDArrayArray_t = std::array<ABCDArray_t<Ns...>, N>;

inline auto operator==(AB_t lhs, AB_t rhs)
    -> bool
{
    return (lhs.a == rhs.a && lhs.b == rhs.b);
}

inline auto operator==(CD_t lhs, CD_t rhs)
    -> bool
{
    return (lhs.c == rhs.c && lhs.d == rhs.d);
}

inline auto operator==(AB_CD_t lhs, AB_CD_t rhs)
    -> bool
{
    return (lhs.ab == rhs.ab && lhs.cd == rhs.cd);
}

template<std::size_t... Ns>
inline auto operator==(ABCDArray_t<Ns...> lhs, ABCDArray_t<Ns...> rhs)
    -> bool
{
    return (lhs.a == rhs.a && lhs.b == rhs.b &&
            lhs.c == rhs.c && lhs.d == rhs.d);
}

#endif
