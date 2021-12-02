// SPDX-FileCopyrightText: 2021 SanderTheDragon <sanderthedragon@zoho.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <array>
#include <cstddef>
#include <memory>

#include <gtest/gtest.h>

#include "scppl/binary/Binary.hpp"

#include "Data.hpp"

template<std::size_t N>
void assertDataEqual(std::array<char, N> data,
                     std::array<char, N> expected)
{
    for (std::size_t i = 0; i < N; ++i)
        ASSERT_EQ(data.at(i), expected.at(i));
}

template<std::size_t N, std::size_t... Ns>
requires((Ns + ...) == N)
void assertDataEqual(std::array<char, N> data,
                     std::array<char, Ns>... expected)
{
    assertDataEqual(data, combineArray(expected...));
}

// NOLINTBEGIN: Macros required here
#define DATA_NAME(variable) variable ## Data

#define ASSERT_PACKED_DATA_EQUAL(...) \
    assertDataEqual(scppl::Binary::pack(__VA_ARGS__), \
                    FOR_EACH(DATA_NAME, __VA_ARGS__))
// NOLINTEND

// NOLINTNEXTLINE: External
TEST(BinaryPack, OneType)
{
    ASSERT_PACKED_DATA_EQUAL(A);
    ASSERT_PACKED_DATA_EQUAL(B);
    ASSERT_PACKED_DATA_EQUAL(C);
    ASSERT_PACKED_DATA_EQUAL(D);
}

// NOLINTNEXTLINE: External
TEST(BinaryPack, TwoType)
{
    ASSERT_PACKED_DATA_EQUAL(A, B);
    ASSERT_PACKED_DATA_EQUAL(B, C);
    ASSERT_PACKED_DATA_EQUAL(C, D);
    ASSERT_PACKED_DATA_EQUAL(D, A);
}

// NOLINTNEXTLINE: External
TEST(BinaryPack, ThreeType)
{
    ASSERT_PACKED_DATA_EQUAL(A, B, C);
    ASSERT_PACKED_DATA_EQUAL(B, C, D);
    ASSERT_PACKED_DATA_EQUAL(C, D, A);
    ASSERT_PACKED_DATA_EQUAL(D, A, B);
}

// NOLINTNEXTLINE: External
TEST(BinaryPack, FourType)
{
    ASSERT_PACKED_DATA_EQUAL(A, B, C, D);
    ASSERT_PACKED_DATA_EQUAL(B, C, D, A);
    ASSERT_PACKED_DATA_EQUAL(C, D, A, B);
    ASSERT_PACKED_DATA_EQUAL(D, A, B, C);
}

// NOLINTNEXTLINE: External
TEST(BinaryPack, TwoTypeStruct)
{
    ASSERT_PACKED_DATA_EQUAL(AB);
    ASSERT_PACKED_DATA_EQUAL(CD);
}

// NOLINTNEXTLINE: External
TEST(BinaryPack, TwoTypeStructStruct)
{
    ASSERT_PACKED_DATA_EQUAL(AB_CD);
}
