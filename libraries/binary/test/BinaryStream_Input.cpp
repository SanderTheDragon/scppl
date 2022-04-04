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
#define ASSERT_INPUT_VALUES_EQUAL(endian, suffix, ...) \
    auto [ string, stream ] = toStream(FOR_EACH(DATA_NAME_ ## suffix, \
                                                __VA_ARGS__)); \
    assertValuesEqual(scppl::BinaryInputStream<endian>(stream) \
                          .read<FOR_EACH(TYPE_OF, __VA_ARGS__)>(), \
                      {__VA_ARGS__})

#define ASSERT_INPUT_VALUES_EQUAL_LE(...) \
    ASSERT_INPUT_VALUES_EQUAL(std::endian::little, LE, __VA_ARGS__)
#define ASSERT_INPUT_VALUES_EQUAL_BE(...) \
    ASSERT_INPUT_VALUES_EQUAL(std::endian::big, BE, __VA_ARGS__)
// NOLINTEND(cppcoreguidelines-macro-usage)

TEST(BinaryStreamInput, LittleEndianReadType)
{
    ASSERT_INPUT_VALUES_EQUAL_LE(A, B, C, D);
}

TEST(BinaryStreamInput, LittleEndianReadArray)
{
    ASSERT_INPUT_VALUES_EQUAL_LE(AArray, BArray, CArray, DArray);
}

TEST(BinaryStreamInput, LittleEndianReadStruct)
{
    ASSERT_INPUT_VALUES_EQUAL_LE(AB_CD);
}

TEST(BinaryStreamInput, BigEndianReadType)
{
    ASSERT_INPUT_VALUES_EQUAL_BE(A, B, C, D);
}

TEST(BinaryStreamInput, BigEndianReadArray)
{
    ASSERT_INPUT_VALUES_EQUAL_BE(AArray, BArray, CArray, DArray);
}

TEST(BinaryStreamInput, BigEndianReadStruct)
{
    ASSERT_INPUT_VALUES_EQUAL_BE(AB_CD);
}
