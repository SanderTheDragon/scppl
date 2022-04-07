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

template<typename CharT, std::size_t N>
void decodeAndAssert(std::basic_string_view<CharT> expected,
                     std::string_view encoding,
                     ByteArray<N> data)
{
    auto string = scppl::BinaryString<char, CharT>::decode(data, encoding);

    ASSERT_EQ(std::ranges::size(string), std::ranges::size(expected));
    for (std::size_t i = 0; i < std::ranges::size(string); ++i)
        ASSERT_EQ(string.at(i), expected.at(i));
}

TEST(BinaryStringDecode, ENChar8)
{
    if constexpr(SCPPL_CONFIG_BINARY_USE_ICU)
    {
        decodeAndAssert<char8_t>(ENChar8Text, "ASCII", ENTextASCIIData);
        decodeAndAssert<char8_t>(ENChar8Text, "UTF-8", ENTextUTF8Data);
        decodeAndAssert<char8_t>(ENChar8Text, "UTF-16", ENTextUTF16Data);
    }
}

TEST(BinaryStringDecode, ENChar16)
{
    if constexpr(SCPPL_CONFIG_BINARY_USE_ICU)
    {
        decodeAndAssert<char16_t>(ENChar16Text, "ASCII", ENTextASCIIData);
        decodeAndAssert<char16_t>(ENChar16Text, "UTF-8", ENTextUTF8Data);
        decodeAndAssert<char16_t>(ENChar16Text, "UTF-16", ENTextUTF16Data);
    }
}

TEST(BinaryStringDecode, ENChar32)
{
    if constexpr(SCPPL_CONFIG_BINARY_USE_ICU)
    {
        decodeAndAssert<char32_t>(ENChar32Text, "ASCII", ENTextASCIIData);
        decodeAndAssert<char32_t>(ENChar32Text, "UTF-8", ENTextUTF8Data);
        decodeAndAssert<char32_t>(ENChar32Text, "UTF-16", ENTextUTF16Data);
    }
}

TEST(BinaryStringDecode, JPChar8)
{
    if constexpr(SCPPL_CONFIG_BINARY_USE_ICU)
    {
        decodeAndAssert<char8_t>(JPChar8Text, "Shift-JIS", JPTextShiftJISData);
        decodeAndAssert<char8_t>(JPChar8Text, "UTF-8", JPTextUTF8Data);
        decodeAndAssert<char8_t>(JPChar8Text, "UTF-16", JPTextUTF16Data);
    }
}

TEST(BinaryStringDecode, JPChar16)
{
    if constexpr(SCPPL_CONFIG_BINARY_USE_ICU)
    {
        decodeAndAssert<char16_t>(JPChar16Text, "Shift-JIS",
                                  JPTextShiftJISData);
        decodeAndAssert<char16_t>(JPChar16Text, "UTF-8", JPTextUTF8Data);
        decodeAndAssert<char16_t>(JPChar16Text, "UTF-16", JPTextUTF16Data);
    }
}

TEST(BinaryStringDecode, JPChar32)
{
    if constexpr(SCPPL_CONFIG_BINARY_USE_ICU)
    {
        decodeAndAssert<char32_t>(JPChar32Text, "Shift-JIS",
                                  JPTextShiftJISData);
        decodeAndAssert<char32_t>(JPChar32Text, "UTF-8", JPTextUTF8Data);
        decodeAndAssert<char32_t>(JPChar32Text, "UTF-16", JPTextUTF16Data);
    }
}
