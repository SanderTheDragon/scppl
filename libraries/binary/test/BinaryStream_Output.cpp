// SPDX-FileCopyrightText: 2021-2022 SanderTheDragon <sanderthedragon@zoho.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <array>
#include <bit>
#include <memory>
#include <tuple>
#include <type_traits>

#include <gtest/gtest.h>

#include "scppl/binary/BinaryStream.hpp"

#include "Data.hpp"
#include "Utility.hpp"
#include "Values.hpp"

// NOLINTBEGIN(cppcoreguidelines-macro-usage): Macros required here
#define ASSERT_OUTPUT_DATA_EQUAL(endian, suffix, ...) \
    std::ostringstream stream{}; \
    scppl::BinaryOutputStream<endian>(stream).write(__VA_ARGS__); \
    assertDataEqual(fromStream<scppl::lengthOf<FOR_EACH(TYPE_OF, \
                                               __VA_ARGS__)>()>(stream), \
                    FOR_EACH(DATA_NAME_ ## suffix, __VA_ARGS__))

#define ASSERT_OUTPUT_DATA_EQUAL_LE(...) \
    ASSERT_OUTPUT_DATA_EQUAL(std::endian::little, LE, __VA_ARGS__)
#define ASSERT_OUTPUT_DATA_EQUAL_BE(...) \
    ASSERT_OUTPUT_DATA_EQUAL(std::endian::big, BE, __VA_ARGS__)
// NOLINTEND(cppcoreguidelines-macro-usage)

TEST(BinaryStreamOutput, LittleEndianWriteType)
{
    ASSERT_OUTPUT_DATA_EQUAL_LE(A, B, C, D);
}

TEST(BinaryStreamOutput, LittleEndianWriteArray)
{
    ASSERT_OUTPUT_DATA_EQUAL_LE(AArray, BArray, CArray, DArray);
}

TEST(BinaryStreamOutput, LittleEndianWriteStruct)
{
    ASSERT_OUTPUT_DATA_EQUAL_LE(AB_CD);
}

TEST(BinaryStreamOutput, BigEndianWriteType)
{
    ASSERT_OUTPUT_DATA_EQUAL_BE(A, B, C, D);
}

TEST(BinaryStreamOutput, BigEndianWriteArray)
{
    ASSERT_OUTPUT_DATA_EQUAL_BE(AArray, BArray, CArray, DArray);
}

TEST(BinaryStreamOutput, BigEndianWriteStruct)
{
    ASSERT_OUTPUT_DATA_EQUAL_BE(AB_CD);
}
