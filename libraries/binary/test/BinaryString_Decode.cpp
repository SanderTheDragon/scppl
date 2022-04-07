// SPDX-FileCopyrightText: 2021-2022 SanderTheDragon <sanderthedragon@zoho.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <cstddef>
#include <string>
#include <string_view>

#include <gtest/gtest.h>

#include "scppl/binary/BinaryString.hpp"

#include "Data.hpp"
#include "Types.hpp"
#include "Utility.hpp"
#include "Values.hpp"

template<typename CharT, std::size_t N>
void decodeAndAssert(std::basic_string<CharT> expected,
                     std::string_view encoding,
                     ByteArray<N> data)
{
    auto string = scppl::BinaryString<char, CharT>::decode(data, encoding);

    assertStringEqual(string, expected);
}

TEST(BinaryStringDecode, ENChar8)
{
    if constexpr(SCPPL_CONFIG_BINARY_USE_ICU)
    {
        decodeAndAssert(ENChar8Text, "ASCII", ENTextASCIIData);
        decodeAndAssert(ENChar8Text, "UTF-8", ENTextUTF8Data);
        decodeAndAssert(ENChar8Text, "UTF-16", ENTextUTF16Data);
    }
}

TEST(BinaryStringDecode, ENChar16)
{
    if constexpr(SCPPL_CONFIG_BINARY_USE_ICU)
    {
        decodeAndAssert(ENChar16Text, "ASCII", ENTextASCIIData);
        decodeAndAssert(ENChar16Text, "UTF-8", ENTextUTF8Data);
        decodeAndAssert(ENChar16Text, "UTF-16", ENTextUTF16Data);
    }
}

TEST(BinaryStringDecode, ENChar32)
{
    if constexpr(SCPPL_CONFIG_BINARY_USE_ICU)
    {
        decodeAndAssert(ENChar32Text, "ASCII", ENTextASCIIData);
        decodeAndAssert(ENChar32Text, "UTF-8", ENTextUTF8Data);
        decodeAndAssert(ENChar32Text, "UTF-16", ENTextUTF16Data);
    }
}

TEST(BinaryStringDecode, JPChar8)
{
    if constexpr(SCPPL_CONFIG_BINARY_USE_ICU)
    {
        decodeAndAssert(JPChar8Text, "Shift-JIS", JPTextShiftJISData);
        decodeAndAssert(JPChar8Text, "UTF-8", JPTextUTF8Data);
        decodeAndAssert(JPChar8Text, "UTF-16", JPTextUTF16Data);
    }
}

TEST(BinaryStringDecode, JPChar16)
{
    if constexpr(SCPPL_CONFIG_BINARY_USE_ICU)
    {
        decodeAndAssert(JPChar16Text, "Shift-JIS", JPTextShiftJISData);
        decodeAndAssert(JPChar16Text, "UTF-8", JPTextUTF8Data);
        decodeAndAssert(JPChar16Text, "UTF-16", JPTextUTF16Data);
    }
}

TEST(BinaryStringDecode, JPChar32)
{
    if constexpr(SCPPL_CONFIG_BINARY_USE_ICU)
    {
        decodeAndAssert(JPChar32Text, "Shift-JIS", JPTextShiftJISData);
        decodeAndAssert(JPChar32Text, "UTF-8", JPTextUTF8Data);
        decodeAndAssert(JPChar32Text, "UTF-16", JPTextUTF16Data);
    }
}
