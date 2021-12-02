// SPDX-FileCopyrightText: 2021 SanderTheDragon <sanderthedragon@zoho.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <bit>
#include <cstddef>
#include <tuple>
#include <type_traits>
#include <vector>

#include <gtest/gtest.h>

#include "scppl/binary/Binary.hpp"

#include "Data.hpp"

// NOLINTBEGIN: Macros required here
#define DATA_NAME_LE(variable) variable ## DataLE
#define DATA_NAME_BE(variable) variable ## DataBE
#define TYPE_OF(variable) std::remove_const_t<decltype(variable)>

#define ASSERT_UNPACKED_VALUES_EQUAL(endian, prefix, ...) \
    assertValuesEqual( \
        scppl::Binary::unpack<endian, FOR_EACH(TYPE_OF, __VA_ARGS__)>( \
            combineArrays(FOR_EACH(DATA_NAME_ ## prefix, __VA_ARGS__))), \
                          {__VA_ARGS__})

#define ASSERT_UNPACKED_VALUES_EQUAL_LE(...) \
    ASSERT_UNPACKED_VALUES_EQUAL(std::endian::little, LE, __VA_ARGS__)
#define ASSERT_UNPACKED_VALUES_EQUAL_BE(...) \
    ASSERT_UNPACKED_VALUES_EQUAL(std::endian::big, BE, __VA_ARGS__)
// NOLINTEND

template<std::size_t I = 0, typename... Ts>
requires(I == sizeof...(Ts))
void assertValuesEqual(std::tuple<Ts...> /* values */,
                       std::tuple<Ts...> /* expected */)
{

}

template<std::size_t I = 0, typename... Ts>
requires(I < sizeof...(Ts))
void assertValuesEqual(std::tuple<Ts...> values,
                       std::tuple<Ts...> expected)
{
    ASSERT_EQ(std::get<I>(values), std::get<I>(expected));

    assertValuesEqual<I + 1>(values, expected);
}

// NOLINTNEXTLINE: External
TEST(BinaryUnpack, LittleEndianOneType)
{
    ASSERT_UNPACKED_VALUES_EQUAL_LE(A);
    ASSERT_UNPACKED_VALUES_EQUAL_LE(B);
    ASSERT_UNPACKED_VALUES_EQUAL_LE(C);
    ASSERT_UNPACKED_VALUES_EQUAL_LE(D);
}

// NOLINTNEXTLINE: External
TEST(BinaryUnpack, LittleEndianTwoType)
{
    ASSERT_UNPACKED_VALUES_EQUAL_LE(A, B);
    ASSERT_UNPACKED_VALUES_EQUAL_LE(B, C);
    ASSERT_UNPACKED_VALUES_EQUAL_LE(C, D);
    ASSERT_UNPACKED_VALUES_EQUAL_LE(D, A);
}

// NOLINTNEXTLINE: External
TEST(BinaryUnpack, LittleEndianThreeType)
{
    ASSERT_UNPACKED_VALUES_EQUAL_LE(A, B, C);
    ASSERT_UNPACKED_VALUES_EQUAL_LE(B, C, D);
    ASSERT_UNPACKED_VALUES_EQUAL_LE(C, D, A);
    ASSERT_UNPACKED_VALUES_EQUAL_LE(D, A, B);
}

// NOLINTNEXTLINE: External
TEST(BinaryUnpack, LittleEndianFourType)
{
    ASSERT_UNPACKED_VALUES_EQUAL_LE(A, B, C, D);
    ASSERT_UNPACKED_VALUES_EQUAL_LE(B, C, D, A);
    ASSERT_UNPACKED_VALUES_EQUAL_LE(C, D, A, B);
    ASSERT_UNPACKED_VALUES_EQUAL_LE(D, A, B, C);
}

// NOLINTNEXTLINE: External
TEST(BinaryUnpack, LittleEndianTwoTypeStruct)
{
    ASSERT_UNPACKED_VALUES_EQUAL_LE(AB);
    ASSERT_UNPACKED_VALUES_EQUAL_LE(CD);
}

// NOLINTNEXTLINE: External
TEST(BinaryUnpack, LittleEndianTwoTypeStructStruct)
{
    ASSERT_UNPACKED_VALUES_EQUAL_LE(AB_CD);
}

// NOLINTNEXTLINE: External
TEST(BinaryUnpack, BigEndianOneType)
{
    ASSERT_UNPACKED_VALUES_EQUAL_BE(A);
    ASSERT_UNPACKED_VALUES_EQUAL_BE(B);
    ASSERT_UNPACKED_VALUES_EQUAL_BE(C);
    ASSERT_UNPACKED_VALUES_EQUAL_BE(D);
}

// NOLINTNEXTLINE: External
TEST(BinaryUnpack, BigEndianTwoType)
{
    ASSERT_UNPACKED_VALUES_EQUAL_BE(A, B);
    ASSERT_UNPACKED_VALUES_EQUAL_BE(B, C);
    ASSERT_UNPACKED_VALUES_EQUAL_BE(C, D);
    ASSERT_UNPACKED_VALUES_EQUAL_BE(D, A);
}

// NOLINTNEXTLINE: External
TEST(BinaryUnpack, BigEndianThreeType)
{
    ASSERT_UNPACKED_VALUES_EQUAL_BE(A, B, C);
    ASSERT_UNPACKED_VALUES_EQUAL_BE(B, C, D);
    ASSERT_UNPACKED_VALUES_EQUAL_BE(C, D, A);
    ASSERT_UNPACKED_VALUES_EQUAL_BE(D, A, B);
}

// NOLINTNEXTLINE: External
TEST(BinaryUnpack, BigEndianFourType)
{
    ASSERT_UNPACKED_VALUES_EQUAL_BE(A, B, C, D);
    ASSERT_UNPACKED_VALUES_EQUAL_BE(B, C, D, A);
    ASSERT_UNPACKED_VALUES_EQUAL_BE(C, D, A, B);
    ASSERT_UNPACKED_VALUES_EQUAL_BE(D, A, B, C);
}

// NOLINTNEXTLINE: External
TEST(BinaryUnpack, BigEndianTwoTypeStruct)
{
    ASSERT_UNPACKED_VALUES_EQUAL_BE(AB);
    ASSERT_UNPACKED_VALUES_EQUAL_BE(CD);
}

// NOLINTNEXTLINE: External
TEST(BinaryUnpack, BigEndianTwoTypeStructStruct)
{
    ASSERT_UNPACKED_VALUES_EQUAL_BE(AB_CD);
}
