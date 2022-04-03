// SPDX-FileCopyrightText: 2021-2022 SanderTheDragon <sanderthedragon@zoho.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <array>
#include <bit>
#include <type_traits>
#include <vector>

#include <gtest/gtest.h>

#include "scppl/binary/Binary.hpp"

#include "Data.hpp"
#include "Types.hpp"
#include "Utility.hpp"
#include "Values.hpp"

// NOLINTBEGIN(cppcoreguidelines-macro-usage): Macros required here
#define ASSERT_UNPACKED_VALUES_EQUAL(endian, suffix, ...) \
    assertValuesEqual( \
        scppl::Binary<endian>::unpack<FOR_EACH(TYPE_OF, __VA_ARGS__)>( \
            combineArrays(FOR_EACH(DATA_NAME_ ## suffix, __VA_ARGS__))), \
                          {__VA_ARGS__})

#define ASSERT_UNPACKED_VALUES_EQUAL_LE(...) \
    ASSERT_UNPACKED_VALUES_EQUAL(std::endian::little, LE, __VA_ARGS__)
#define ASSERT_UNPACKED_VALUES_EQUAL_BE(...) \
    ASSERT_UNPACKED_VALUES_EQUAL(std::endian::big, BE, __VA_ARGS__)
// NOLINTEND(cppcoreguidelines-macro-usage)

TEST(BinaryUnpack, LittleEndianOneType)
{
    ASSERT_UNPACKED_VALUES_EQUAL_LE(A);
    ASSERT_UNPACKED_VALUES_EQUAL_LE(B);
    ASSERT_UNPACKED_VALUES_EQUAL_LE(C);
    ASSERT_UNPACKED_VALUES_EQUAL_LE(D);
}

TEST(BinaryUnpack, LittleEndianTwoType)
{
    ASSERT_UNPACKED_VALUES_EQUAL_LE(A, B);
    ASSERT_UNPACKED_VALUES_EQUAL_LE(B, C);
    ASSERT_UNPACKED_VALUES_EQUAL_LE(C, D);
    ASSERT_UNPACKED_VALUES_EQUAL_LE(D, A);
}

TEST(BinaryUnpack, LittleEndianThreeType)
{
    ASSERT_UNPACKED_VALUES_EQUAL_LE(A, B, C);
    ASSERT_UNPACKED_VALUES_EQUAL_LE(B, C, D);
    ASSERT_UNPACKED_VALUES_EQUAL_LE(C, D, A);
    ASSERT_UNPACKED_VALUES_EQUAL_LE(D, A, B);
}

TEST(BinaryUnpack, LittleEndianFourType)
{
    ASSERT_UNPACKED_VALUES_EQUAL_LE(A, B, C, D);
    ASSERT_UNPACKED_VALUES_EQUAL_LE(B, C, D, A);
    ASSERT_UNPACKED_VALUES_EQUAL_LE(C, D, A, B);
    ASSERT_UNPACKED_VALUES_EQUAL_LE(D, A, B, C);
}

TEST(BinaryUnpack, LittleEndianArray)
{
    ASSERT_UNPACKED_VALUES_EQUAL_LE(AArray);
    ASSERT_UNPACKED_VALUES_EQUAL_LE(BArray);
    ASSERT_UNPACKED_VALUES_EQUAL_LE(CArray);
    ASSERT_UNPACKED_VALUES_EQUAL_LE(DArray);
}

TEST(BinaryUnpack, LittleEndianStruct)
{
    if constexpr(std::endian::native == std::endian::little ||
                 SCPPL_CONFIG_BINARY_USE_PFR)
    {
        ASSERT_UNPACKED_VALUES_EQUAL_LE(AB);
        ASSERT_UNPACKED_VALUES_EQUAL_LE(CD);
    }
}

TEST(BinaryUnpack, LittleEndianStructStruct)
{
    if constexpr(std::endian::native == std::endian::little ||
                 SCPPL_CONFIG_BINARY_USE_PFR)
    {
        ASSERT_UNPACKED_VALUES_EQUAL_LE(AB_CD);
    }
}

TEST(BinaryUnpack, LittleEndianStructArray)
{
    if constexpr(std::endian::native == std::endian::little ||
                 SCPPL_CONFIG_BINARY_USE_PFR)
    {
        ASSERT_UNPACKED_VALUES_EQUAL_LE(AB_CDArray);
    }
}

TEST(BinaryUnpack, LittleEndianArrayStruct)
{
    if constexpr(std::endian::native == std::endian::little ||
                 SCPPL_CONFIG_BINARY_USE_PFR)
    {
        ASSERT_UNPACKED_VALUES_EQUAL_LE(ABCDArray);
    }
}

TEST(BinaryUnpack, LittleEndianArrayStructArray)
{
    if constexpr(std::endian::native == std::endian::little ||
                 SCPPL_CONFIG_BINARY_USE_PFR)
    {
        ASSERT_UNPACKED_VALUES_EQUAL_LE(ABCDArrayArray);
    }
}

TEST(BinaryUnpack, BigEndianOneType)
{
    ASSERT_UNPACKED_VALUES_EQUAL_BE(A);
    ASSERT_UNPACKED_VALUES_EQUAL_BE(B);
    ASSERT_UNPACKED_VALUES_EQUAL_BE(C);
    ASSERT_UNPACKED_VALUES_EQUAL_BE(D);
}

TEST(BinaryUnpack, BigEndianTwoType)
{
    ASSERT_UNPACKED_VALUES_EQUAL_BE(A, B);
    ASSERT_UNPACKED_VALUES_EQUAL_BE(B, C);
    ASSERT_UNPACKED_VALUES_EQUAL_BE(C, D);
    ASSERT_UNPACKED_VALUES_EQUAL_BE(D, A);
}

TEST(BinaryUnpack, BigEndianThreeType)
{
    ASSERT_UNPACKED_VALUES_EQUAL_BE(A, B, C);
    ASSERT_UNPACKED_VALUES_EQUAL_BE(B, C, D);
    ASSERT_UNPACKED_VALUES_EQUAL_BE(C, D, A);
    ASSERT_UNPACKED_VALUES_EQUAL_BE(D, A, B);
}

TEST(BinaryUnpack, BigEndianFourType)
{
    ASSERT_UNPACKED_VALUES_EQUAL_BE(A, B, C, D);
    ASSERT_UNPACKED_VALUES_EQUAL_BE(B, C, D, A);
    ASSERT_UNPACKED_VALUES_EQUAL_BE(C, D, A, B);
    ASSERT_UNPACKED_VALUES_EQUAL_BE(D, A, B, C);
}

TEST(BinaryUnpack, BigEndianArray)
{
    ASSERT_UNPACKED_VALUES_EQUAL_BE(AArray);
    ASSERT_UNPACKED_VALUES_EQUAL_BE(BArray);
    ASSERT_UNPACKED_VALUES_EQUAL_BE(CArray);
    ASSERT_UNPACKED_VALUES_EQUAL_BE(DArray);
}

TEST(BinaryUnpack, BigEndianStruct)
{
    if constexpr(std::endian::native == std::endian::big ||
                 SCPPL_CONFIG_BINARY_USE_PFR)
    {
        ASSERT_UNPACKED_VALUES_EQUAL_BE(AB);
        ASSERT_UNPACKED_VALUES_EQUAL_BE(CD);
    }
}

TEST(BinaryUnpack, BigEndianStructStruct)
{
    if constexpr(std::endian::native == std::endian::big ||
                 SCPPL_CONFIG_BINARY_USE_PFR)
    {
        ASSERT_UNPACKED_VALUES_EQUAL_BE(AB_CD);
    }
}

TEST(BinaryUnpack, BigEndianStructArray)
{
    if constexpr(std::endian::native == std::endian::big ||
                 SCPPL_CONFIG_BINARY_USE_PFR)
    {
        ASSERT_UNPACKED_VALUES_EQUAL_BE(AB_CDArray);
    }
}

TEST(BinaryUnpack, BigEndianArrayStruct)
{
    if constexpr(std::endian::native == std::endian::big ||
                 SCPPL_CONFIG_BINARY_USE_PFR)
    {
        ASSERT_UNPACKED_VALUES_EQUAL_BE(ABCDArray);
    }
}

TEST(BinaryUnpack, BigEndianArrayStructArray)
{
    if constexpr(std::endian::native == std::endian::big ||
                 SCPPL_CONFIG_BINARY_USE_PFR)
    {
        ASSERT_UNPACKED_VALUES_EQUAL_BE(ABCDArrayArray);
    }
}
