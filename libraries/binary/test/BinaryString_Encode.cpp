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
void encodeAndAssert(std::basic_string<CharT> string,
                     std::string_view encoding,
                     ByteArray<N> expected)
{
    auto bytes = scppl::BinaryString<char, CharT>::encode(string, encoding);

    assertDataEqual(bytes, expected);
}

TEST(BinaryStringEncode, ENChar8)
{
    if constexpr(SCPPL_CONFIG_BINARY_USE_ICU)
    {
        encodeAndAssert(ENChar8Text, "ASCII", ENTextASCIIData);
        encodeAndAssert(ENChar8Text, "UTF-8", ENTextUTF8Data);
        encodeAndAssert(ENChar8Text, "UTF-16", ENTextUTF16Data);
    }
}

TEST(BinaryStringEncode, ENChar16)
{
    if constexpr(SCPPL_CONFIG_BINARY_USE_ICU)
    {
        encodeAndAssert(ENChar16Text, "ASCII", ENTextASCIIData);
        encodeAndAssert(ENChar16Text, "UTF-8", ENTextUTF8Data);
        encodeAndAssert(ENChar16Text, "UTF-16", ENTextUTF16Data);
    }
}

TEST(BinaryStringEncode, ENChar32)
{
    if constexpr(SCPPL_CONFIG_BINARY_USE_ICU)
    {
        encodeAndAssert(ENChar32Text, "ASCII", ENTextASCIIData);
        encodeAndAssert(ENChar32Text, "UTF-8", ENTextUTF8Data);
        encodeAndAssert(ENChar32Text, "UTF-16", ENTextUTF16Data);
    }
}

TEST(BinaryStringEncode, JPChar8)
{
    if constexpr(SCPPL_CONFIG_BINARY_USE_ICU)
    {
        encodeAndAssert(JPChar8Text, "Shift-JIS", JPTextShiftJISData);
        encodeAndAssert(JPChar8Text, "UTF-8", JPTextUTF8Data);
        encodeAndAssert(JPChar8Text, "UTF-16", JPTextUTF16Data);
    }
}

TEST(BinaryStringEncode, JPChar16)
{
    if constexpr(SCPPL_CONFIG_BINARY_USE_ICU)
    {
        encodeAndAssert(JPChar16Text, "Shift-JIS", JPTextShiftJISData);
        encodeAndAssert(JPChar16Text, "UTF-8", JPTextUTF8Data);
        encodeAndAssert(JPChar16Text, "UTF-16", JPTextUTF16Data);
    }
}

TEST(BinaryStringEncode, JPChar32)
{
    if constexpr(SCPPL_CONFIG_BINARY_USE_ICU)
    {
        encodeAndAssert(JPChar32Text, "Shift-JIS", JPTextShiftJISData);
        encodeAndAssert(JPChar32Text, "UTF-8", JPTextUTF8Data);
        encodeAndAssert(JPChar32Text, "UTF-16", JPTextUTF16Data);
    }
}
