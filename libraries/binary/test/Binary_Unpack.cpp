// SPDX-FileCopyrightText: 2021 SanderTheDragon <sanderthedragon@zoho.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <array>
#include <cstddef>
#include <tuple>
#include <type_traits>
#include <vector>

#include <gtest/gtest.h>

#include "scppl/binary/Binary.hpp"

#include "Data.hpp"

// NOLINTBEGIN: Macros required here
#define DATA_NAME(variable) variable ## Data
#define TYPE_OF(variable)   std::remove_const_t<decltype(variable)>

#define ASSERT_UNPACKED_VALUES_EQUAL(...) \
    assertValuesEqual( \
        scppl::Binary::unpack<FOR_EACH(TYPE_OF, __VA_ARGS__)>( \
            combineArray(FOR_EACH(DATA_NAME, __VA_ARGS__))), {__VA_ARGS__})
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
TEST(BinaryUnpack, OneType)
{
    ASSERT_UNPACKED_VALUES_EQUAL(A);
    ASSERT_UNPACKED_VALUES_EQUAL(B);
    ASSERT_UNPACKED_VALUES_EQUAL(C);
    ASSERT_UNPACKED_VALUES_EQUAL(D);
}

// NOLINTNEXTLINE: External
TEST(BinaryUnpack, TwoType)
{
    ASSERT_UNPACKED_VALUES_EQUAL(A, B);
    ASSERT_UNPACKED_VALUES_EQUAL(B, C);
    ASSERT_UNPACKED_VALUES_EQUAL(C, D);
    ASSERT_UNPACKED_VALUES_EQUAL(D, A);
}

// NOLINTNEXTLINE: External
TEST(BinaryUnpack, ThreeType)
{
    ASSERT_UNPACKED_VALUES_EQUAL(A, B, C);
    ASSERT_UNPACKED_VALUES_EQUAL(B, C, D);
    ASSERT_UNPACKED_VALUES_EQUAL(C, D, A);
    ASSERT_UNPACKED_VALUES_EQUAL(D, A, B);
}

// NOLINTNEXTLINE: External
TEST(BinaryUnpack, FourType)
{
    ASSERT_UNPACKED_VALUES_EQUAL(A, B, C, D);
    ASSERT_UNPACKED_VALUES_EQUAL(B, C, D, A);
    ASSERT_UNPACKED_VALUES_EQUAL(C, D, A, B);
    ASSERT_UNPACKED_VALUES_EQUAL(D, A, B, C);
}

// NOLINTNEXTLINE: External
TEST(BinaryUnpack, TwoTypeStruct)
{
    ASSERT_UNPACKED_VALUES_EQUAL(AB);
    ASSERT_UNPACKED_VALUES_EQUAL(CD);
}

// NOLINTNEXTLINE: External
TEST(BinaryUnpack, TwoTypeStructStruct)
{
    ASSERT_UNPACKED_VALUES_EQUAL(AB_CD);
}
