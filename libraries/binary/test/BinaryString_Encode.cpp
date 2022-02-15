// SPDX-FileCopyrightText: 2021-2022 SanderTheDragon <sanderthedragon@zoho.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <cstddef>
#include <ranges>
#include <string>
#include <string_view>

#include <gtest/gtest.h>

#include "scppl/binary/BinaryString.hpp"

#include "Data.hpp"
#include "Types.hpp"
#include "Values.hpp"

#ifndef SCPPL_CONFIG_BINARY_USE_ICU
#define SCPPL_CONFIG_BINARY_USE_ICU 0
#endif

template<typename CharT, std::size_t N>
void encodeAndAssert(std::basic_string_view<CharT> string,
                     std::string_view encoding,
                     ByteArray<N> expected)
{
    auto bytes = scppl::BinaryString<char, CharT>::encode(string, encoding);

    ASSERT_EQ(std::ranges::size(bytes), N);
    for (std::size_t i = 0; i < N; i++)
        ASSERT_EQ(bytes.at(i), expected.at(i));
}

TEST(BinaryStringEncode, ENChar8)
{
    if constexpr(SCPPL_CONFIG_BINARY_USE_ICU)
    {
        encodeAndAssert<char8_t>(ENChar8Text, "ASCII", ENTextASCIIData);
        encodeAndAssert<char8_t>(ENChar8Text, "UTF-8", ENTextUTF8Data);
        encodeAndAssert<char8_t>(ENChar8Text, "UTF-16", ENTextUTF16Data);
    }
}

TEST(BinaryStringEncode, ENChar16)
{
    if constexpr(SCPPL_CONFIG_BINARY_USE_ICU)
    {
        encodeAndAssert<char16_t>(ENChar16Text, "ASCII", ENTextASCIIData);
        encodeAndAssert<char16_t>(ENChar16Text, "UTF-8", ENTextUTF8Data);
        encodeAndAssert<char16_t>(ENChar16Text, "UTF-16", ENTextUTF16Data);
    }
}

TEST(BinaryStringEncode, ENChar32)
{
    if constexpr(SCPPL_CONFIG_BINARY_USE_ICU)
    {
        encodeAndAssert<char32_t>(ENChar32Text, "ASCII", ENTextASCIIData);
        encodeAndAssert<char32_t>(ENChar32Text, "UTF-8", ENTextUTF8Data);
        encodeAndAssert<char32_t>(ENChar32Text, "UTF-16", ENTextUTF16Data);
    }
}

TEST(BinaryStringEncode, JPChar8)
{
    if constexpr(SCPPL_CONFIG_BINARY_USE_ICU)
    {
        encodeAndAssert<char8_t>(JPChar8Text, "Shift-JIS", JPTextShiftJISData);
        encodeAndAssert<char8_t>(JPChar8Text, "UTF-8", JPTextUTF8Data);
        encodeAndAssert<char8_t>(JPChar8Text, "UTF-16", JPTextUTF16Data);
    }
}

TEST(BinaryStringEncode, JPChar16)
{
    if constexpr(SCPPL_CONFIG_BINARY_USE_ICU)
    {
        encodeAndAssert<char16_t>(JPChar16Text, "Shift-JIS",
                                  JPTextShiftJISData);

        encodeAndAssert<char16_t>(JPChar16Text, "UTF-8", JPTextUTF8Data);
        encodeAndAssert<char16_t>(JPChar16Text, "UTF-16", JPTextUTF16Data);
    }
}

TEST(BinaryStringEncode, JPChar32)
{
    if constexpr(SCPPL_CONFIG_BINARY_USE_ICU)
    {
        encodeAndAssert<char32_t>(JPChar32Text, "Shift-JIS",
                                  JPTextShiftJISData);

        encodeAndAssert<char32_t>(JPChar32Text, "UTF-8", JPTextUTF8Data);
        encodeAndAssert<char32_t>(JPChar32Text, "UTF-16", JPTextUTF16Data);
    }
}
