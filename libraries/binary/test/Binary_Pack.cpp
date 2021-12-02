// SPDX-FileCopyrightText: 2021 SanderTheDragon <sanderthedragon@zoho.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <array>
#include <bit>
#include <cstddef>
#include <memory>

#include <gtest/gtest.h>

#ifdef SCPPL_CONFING_BINARY_USE_PFR
#include <boost/pfr/core.hpp>
#endif

#include "scppl/binary/Binary.hpp"

#include "Data.hpp"

#ifndef SCPPL_CONFING_BINARY_USE_PFR
#define SCPPL_CONFING_BINARY_USE_PFR 0
#endif

// NOLINTBEGIN: Macros required here
#define DATA_NAME_LE(variable) variable ## DataLE
#define DATA_NAME_BE(variable) variable ## DataBE

#define ASSERT_PACKED_DATA_EQUAL(endian, prefix, ...) \
    assertDataEqual(scppl::Binary::pack<endian>(__VA_ARGS__), \
                    FOR_EACH(DATA_NAME_ ## prefix, __VA_ARGS__))

#define ASSERT_PACKED_DATA_EQUAL_LE(...) \
    ASSERT_PACKED_DATA_EQUAL(std::endian::little, LE, __VA_ARGS__)
#define ASSERT_PACKED_DATA_EQUAL_BE(...) \
    ASSERT_PACKED_DATA_EQUAL(std::endian::big, BE, __VA_ARGS__)
// NOLINTEND

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
    assertDataEqual(data, combineArrays(expected...));
}

// NOLINTNEXTLINE: External
TEST(BinaryPack, LittleEndianOneType)
{
    ASSERT_PACKED_DATA_EQUAL_LE(A);
    ASSERT_PACKED_DATA_EQUAL_LE(B);
    ASSERT_PACKED_DATA_EQUAL_LE(C);
    ASSERT_PACKED_DATA_EQUAL_LE(D);
}

// NOLINTNEXTLINE: External
TEST(BinaryPack, LittleEndianTwoType)
{
    ASSERT_PACKED_DATA_EQUAL_LE(A, B);
    ASSERT_PACKED_DATA_EQUAL_LE(B, C);
    ASSERT_PACKED_DATA_EQUAL_LE(C, D);
    ASSERT_PACKED_DATA_EQUAL_LE(D, A);
}

// NOLINTNEXTLINE: External
TEST(BinaryPack, LittleEndianThreeType)
{
    ASSERT_PACKED_DATA_EQUAL_LE(A, B, C);
    ASSERT_PACKED_DATA_EQUAL_LE(B, C, D);
    ASSERT_PACKED_DATA_EQUAL_LE(C, D, A);
    ASSERT_PACKED_DATA_EQUAL_LE(D, A, B);
}

// NOLINTNEXTLINE: External
TEST(BinaryPack, LittleEndianFourType)
{
    ASSERT_PACKED_DATA_EQUAL_LE(A, B, C, D);
    ASSERT_PACKED_DATA_EQUAL_LE(B, C, D, A);
    ASSERT_PACKED_DATA_EQUAL_LE(C, D, A, B);
    ASSERT_PACKED_DATA_EQUAL_LE(D, A, B, C);
}

// NOLINTNEXTLINE: External
TEST(BinaryPack, LittleEndianTwoTypeStruct)
{
    if (std::endian::native == std::endian::little ||
        SCPPL_CONFING_BINARY_USE_PFR)
    {
        ASSERT_PACKED_DATA_EQUAL_LE(AB);
        ASSERT_PACKED_DATA_EQUAL_LE(CD);
    }
}

// NOLINTNEXTLINE: External
TEST(BinaryPack, LittleEndianTwoTypeStructStruct)
{
    if (std::endian::native == std::endian::little ||
        SCPPL_CONFING_BINARY_USE_PFR)
    {
        ASSERT_PACKED_DATA_EQUAL_LE(AB_CD);
    }
}

// NOLINTNEXTLINE: External
TEST(BinaryPack, BigEndianOneType)
{
    ASSERT_PACKED_DATA_EQUAL_BE(A);
    ASSERT_PACKED_DATA_EQUAL_BE(B);
    ASSERT_PACKED_DATA_EQUAL_BE(C);
    ASSERT_PACKED_DATA_EQUAL_BE(D);
}

// NOLINTNEXTLINE: External
TEST(BinaryPack, BigEndianTwoType)
{
    ASSERT_PACKED_DATA_EQUAL_BE(A, B);
    ASSERT_PACKED_DATA_EQUAL_BE(B, C);
    ASSERT_PACKED_DATA_EQUAL_BE(C, D);
    ASSERT_PACKED_DATA_EQUAL_BE(D, A);
}

// NOLINTNEXTLINE: External
TEST(BinaryPack, BigEndianThreeType)
{
    ASSERT_PACKED_DATA_EQUAL_BE(A, B, C);
    ASSERT_PACKED_DATA_EQUAL_BE(B, C, D);
    ASSERT_PACKED_DATA_EQUAL_BE(C, D, A);
    ASSERT_PACKED_DATA_EQUAL_BE(D, A, B);
}

// NOLINTNEXTLINE: External
TEST(BinaryPack, BigEndianFourType)
{
    ASSERT_PACKED_DATA_EQUAL_BE(A, B, C, D);
    ASSERT_PACKED_DATA_EQUAL_BE(B, C, D, A);
    ASSERT_PACKED_DATA_EQUAL_BE(C, D, A, B);
    ASSERT_PACKED_DATA_EQUAL_BE(D, A, B, C);
}

// NOLINTNEXTLINE: External
TEST(BinaryPack, BigEndianTwoTypeStruct)
{
    if (std::endian::native == std::endian::big ||
        SCPPL_CONFING_BINARY_USE_PFR)
    {
        ASSERT_PACKED_DATA_EQUAL_BE(AB);
        ASSERT_PACKED_DATA_EQUAL_BE(CD);
    }
}

// NOLINTNEXTLINE: External
TEST(BinaryPack, BigEndianTwoTypeStructStruct)
{
    if (std::endian::native == std::endian::big ||
        SCPPL_CONFING_BINARY_USE_PFR)
    {
        ASSERT_PACKED_DATA_EQUAL_BE(AB_CD);
    }
}
