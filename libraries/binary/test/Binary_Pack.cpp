// SPDX-FileCopyrightText: 2021-2022 SanderTheDragon <sanderthedragon@zoho.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <array>
#include <bit>
#include <cstddef>
#include <memory>

#include <gtest/gtest.h>

#include "scppl/binary/Binary.hpp"

#include "Data.hpp"
#include "Types.hpp"
#include "Utility.hpp"
#include "Values.hpp"

// NOLINTBEGIN(cppcoreguidelines-macro-usage): Macros required here
#define DATA_NAME_LE(variable) variable ## DataLE
#define DATA_NAME_BE(variable) variable ## DataBE

#define ASSERT_PACKED_DATA_EQUAL(endian, suffix, ...) \
    assertDataEqual(scppl::Binary<endian>::pack(__VA_ARGS__), \
                    FOR_EACH(DATA_NAME_ ## suffix, __VA_ARGS__))

#define ASSERT_PACKED_DATA_EQUAL_LE(...) \
    ASSERT_PACKED_DATA_EQUAL(std::endian::little, LE, __VA_ARGS__)
#define ASSERT_PACKED_DATA_EQUAL_BE(...) \
    ASSERT_PACKED_DATA_EQUAL(std::endian::big, BE, __VA_ARGS__)
// NOLINTEND(cppcoreguidelines-macro-usage)

TEST(BinaryPack, LittleEndianOneType)
{
    ASSERT_PACKED_DATA_EQUAL_LE(A);
    ASSERT_PACKED_DATA_EQUAL_LE(B);
    ASSERT_PACKED_DATA_EQUAL_LE(C);
    ASSERT_PACKED_DATA_EQUAL_LE(D);
}

TEST(BinaryPack, LittleEndianTwoType)
{
    ASSERT_PACKED_DATA_EQUAL_LE(A, B);
    ASSERT_PACKED_DATA_EQUAL_LE(B, C);
    ASSERT_PACKED_DATA_EQUAL_LE(C, D);
    ASSERT_PACKED_DATA_EQUAL_LE(D, A);
}

TEST(BinaryPack, LittleEndianThreeType)
{
    ASSERT_PACKED_DATA_EQUAL_LE(A, B, C);
    ASSERT_PACKED_DATA_EQUAL_LE(B, C, D);
    ASSERT_PACKED_DATA_EQUAL_LE(C, D, A);
    ASSERT_PACKED_DATA_EQUAL_LE(D, A, B);
}

TEST(BinaryPack, LittleEndianFourType)
{
    ASSERT_PACKED_DATA_EQUAL_LE(A, B, C, D);
    ASSERT_PACKED_DATA_EQUAL_LE(B, C, D, A);
    ASSERT_PACKED_DATA_EQUAL_LE(C, D, A, B);
    ASSERT_PACKED_DATA_EQUAL_LE(D, A, B, C);
}

TEST(BinaryPack, LittleEndianArray)
{
    ASSERT_PACKED_DATA_EQUAL_LE(AArray);
    ASSERT_PACKED_DATA_EQUAL_LE(BArray);
    ASSERT_PACKED_DATA_EQUAL_LE(CArray);
    ASSERT_PACKED_DATA_EQUAL_LE(DArray);
}

TEST(BinaryPack, LittleEndianStruct)
{
    if constexpr(std::endian::native == std::endian::little ||
                 SCPPL_CONFIG_BINARY_USE_PFR)
    {
        ASSERT_PACKED_DATA_EQUAL_LE(AB);
        ASSERT_PACKED_DATA_EQUAL_LE(CD);
    }
}

TEST(BinaryPack, LittleEndianStructStruct)
{
    if constexpr(std::endian::native == std::endian::little ||
                 SCPPL_CONFIG_BINARY_USE_PFR)
    {
        ASSERT_PACKED_DATA_EQUAL_LE(AB_CD);
    }
}

TEST(BinaryPack, LittleEndianStructArray)
{
    if constexpr(std::endian::native == std::endian::little ||
                 SCPPL_CONFIG_BINARY_USE_PFR)
    {
        ASSERT_PACKED_DATA_EQUAL_LE(AB_CDArray);
    }
}

TEST(BinaryPack, LittleEndianArrayStruct)
{
    if constexpr(std::endian::native == std::endian::little ||
                 SCPPL_CONFIG_BINARY_USE_PFR)
    {
        ASSERT_PACKED_DATA_EQUAL_LE(ABCDArray);
    }
}

TEST(BinaryPack, LittleEndianArrayStructArray)
{
    if constexpr(std::endian::native == std::endian::little ||
                 SCPPL_CONFIG_BINARY_USE_PFR)
    {
        ASSERT_PACKED_DATA_EQUAL_LE(ABCDArrayArray);
    }
}

TEST(BinaryPack, BigEndianOneType)
{
    ASSERT_PACKED_DATA_EQUAL_BE(A);
    ASSERT_PACKED_DATA_EQUAL_BE(B);
    ASSERT_PACKED_DATA_EQUAL_BE(C);
    ASSERT_PACKED_DATA_EQUAL_BE(D);
}

TEST(BinaryPack, BigEndianTwoType)
{
    ASSERT_PACKED_DATA_EQUAL_BE(A, B);
    ASSERT_PACKED_DATA_EQUAL_BE(B, C);
    ASSERT_PACKED_DATA_EQUAL_BE(C, D);
    ASSERT_PACKED_DATA_EQUAL_BE(D, A);
}

TEST(BinaryPack, BigEndianThreeType)
{
    ASSERT_PACKED_DATA_EQUAL_BE(A, B, C);
    ASSERT_PACKED_DATA_EQUAL_BE(B, C, D);
    ASSERT_PACKED_DATA_EQUAL_BE(C, D, A);
    ASSERT_PACKED_DATA_EQUAL_BE(D, A, B);
}

TEST(BinaryPack, BigEndianFourType)
{
    ASSERT_PACKED_DATA_EQUAL_BE(A, B, C, D);
    ASSERT_PACKED_DATA_EQUAL_BE(B, C, D, A);
    ASSERT_PACKED_DATA_EQUAL_BE(C, D, A, B);
    ASSERT_PACKED_DATA_EQUAL_BE(D, A, B, C);
}

TEST(BinaryPack, BigEndianArray)
{
    ASSERT_PACKED_DATA_EQUAL_BE(AArray);
    ASSERT_PACKED_DATA_EQUAL_BE(BArray);
    ASSERT_PACKED_DATA_EQUAL_BE(CArray);
    ASSERT_PACKED_DATA_EQUAL_BE(DArray);
}

TEST(BinaryPack, BigEndianStruct)
{
    if constexpr(std::endian::native == std::endian::big ||
                 SCPPL_CONFIG_BINARY_USE_PFR)
    {
        ASSERT_PACKED_DATA_EQUAL_BE(AB);
        ASSERT_PACKED_DATA_EQUAL_BE(CD);
    }
}

TEST(BinaryPack, BigEndianStructStruct)
{
    if constexpr(std::endian::native == std::endian::big ||
                 SCPPL_CONFIG_BINARY_USE_PFR)
    {
        ASSERT_PACKED_DATA_EQUAL_BE(AB_CD);
    }
}

TEST(BinaryPack, BigEndianStructArray)
{
    if constexpr(std::endian::native == std::endian::big ||
                 SCPPL_CONFIG_BINARY_USE_PFR)
    {
        ASSERT_PACKED_DATA_EQUAL_BE(AB_CDArray);
    }
}

TEST(BinaryPack, BigEndianArrayStruct)
{
    if constexpr(std::endian::native == std::endian::big ||
                 SCPPL_CONFIG_BINARY_USE_PFR)
    {
        ASSERT_PACKED_DATA_EQUAL_BE(ABCDArray);
    }
}

TEST(BinaryPack, BigEndianArrayStructArray)
{
    if constexpr(std::endian::native == std::endian::big ||
                 SCPPL_CONFIG_BINARY_USE_PFR)
    {
        ASSERT_PACKED_DATA_EQUAL_BE(ABCDArrayArray);
    }
}
