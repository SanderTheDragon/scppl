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
void decodeAndAssert(ByteArray<N> data,
                     std::string_view encoding,
                     std::basic_string_view<CharT> expected)
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
        decodeAndAssert<char8_t>(ENTextASCIIData, "ASCII", ENChar8Text);
        decodeAndAssert<char8_t>(ENTextUTF8Data, "UTF-8", ENChar8Text);
        decodeAndAssert<char8_t>(ENTextUTF16Data, "UTF-16", ENChar8Text);
    }
}

TEST(BinaryStringDecode, ENChar16)
{
    if constexpr(SCPPL_CONFIG_BINARY_USE_ICU)
    {
        decodeAndAssert<char16_t>(ENTextASCIIData, "ASCII", ENChar16Text);
        decodeAndAssert<char16_t>(ENTextUTF8Data, "UTF-8", ENChar16Text);
        decodeAndAssert<char16_t>(ENTextUTF16Data, "UTF-16", ENChar16Text);
    }
}

TEST(BinaryStringDecode, ENChar32)
{
    if constexpr(SCPPL_CONFIG_BINARY_USE_ICU)
    {
        decodeAndAssert<char32_t>(ENTextASCIIData, "ASCII", ENChar32Text);
        decodeAndAssert<char32_t>(ENTextUTF8Data, "UTF-8", ENChar32Text);
        decodeAndAssert<char32_t>(ENTextUTF16Data, "UTF-16", ENChar32Text);
    }
}

TEST(BinaryStringDecode, JPChar8)
{
    if constexpr(SCPPL_CONFIG_BINARY_USE_ICU)
    {
        decodeAndAssert<char8_t>(JPTextShiftJISData, "Shift-JIS", JPChar8Text);
        decodeAndAssert<char8_t>(JPTextUTF8Data, "UTF-8", JPChar8Text);
        decodeAndAssert<char8_t>(JPTextUTF16Data, "UTF-16", JPChar8Text);
    }
}

TEST(BinaryStringDecode, JPChar16)
{
    if constexpr(SCPPL_CONFIG_BINARY_USE_ICU)
    {
        decodeAndAssert<char16_t>(JPTextShiftJISData, "Shift-JIS",
                                  JPChar16Text);

        decodeAndAssert<char16_t>(JPTextUTF8Data, "UTF-8", JPChar16Text);
        decodeAndAssert<char16_t>(JPTextUTF16Data, "UTF-16", JPChar16Text);
    }
}

TEST(BinaryStringDecode, JPChar32)
{
    if constexpr(SCPPL_CONFIG_BINARY_USE_ICU)
    {
        decodeAndAssert<char32_t>(JPTextShiftJISData, "Shift-JIS",
                                  JPChar32Text);

        decodeAndAssert<char32_t>(JPTextUTF8Data, "UTF-8", JPChar32Text);
        decodeAndAssert<char32_t>(JPTextUTF16Data, "UTF-16", JPChar32Text);
    }
}
