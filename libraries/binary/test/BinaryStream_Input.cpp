// SPDX-FileCopyrightText: 2021-2022 SanderTheDragon <sanderthedragon@zoho.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <algorithm>
#include <array>
#include <bit>
#include <cstddef>
#include <istream>
#include <ranges>
#include <string>
#include <string_view>
#include <tuple>
#include <utility>

#include <gtest/gtest.h>

#include "scppl/binary/BinaryStream.hpp"

#include "Data.hpp"
#include "Types.hpp"
#include "Utility.hpp"
#include "Values.hpp"

template<std::size_t... Ns>
auto toStream(ByteArray<Ns>... datas)
    -> std::istringstream
{
    auto data = combineArrays(datas...);

    std::string string{};
    string.resize((Ns + ...));

    std::ranges::copy(std::ranges::begin(data), std::ranges::end(data),
                      std::ranges::begin(string));

    std::istringstream stringstream(string);
    stringstream.seekg(0);

    return std::move(stringstream);
}

template<std::endian tEndian, typename... Ts, std::size_t... Ns>
requires(sizeof...(Ts) == sizeof...(Ns))
void readAndAssert(std::tuple<Ts...> expected, ByteArray<Ns>... datas)
{
    auto stringstream = toStream(datas...);
    scppl::BinaryInputStream<tEndian> stream(stringstream);
    auto values = stream.template read<Ts...>();

    assertValuesEqual(values, expected);
}

constexpr auto readAndAssertLE = [](auto&&... args) -> void
{
    readAndAssert<std::endian::little>(std::forward<decltype(args)>(args)...);
};

constexpr auto readAndAssertBE = [](auto&&... args) -> void
{
    readAndAssert<std::endian::big>(std::forward<decltype(args)>(args)...);
};

template<typename CharT, std::size_t... Ns>
void readStringAndAssert(std::basic_string<CharT> expected,
                         std::string_view encoding,
                         ByteArray<Ns>... datas)
{
    auto stringstream = toStream(datas...);
    scppl::BinaryInputStream<> stream(stringstream);
    auto string = stream.readString<CharT>((Ns + ...), encoding);

    assertStringEqual(string, expected);
}

TEST(BinaryStreamInput, LittleEndianReadType)
{
    readAndAssertLE(std::tuple{A, B, C, D},
                    ADataLE, BDataLE, CDataLE, DDataLE);
}

TEST(BinaryStreamInput, LittleEndianReadArray)
{
    readAndAssertLE(std::tuple{AArray, BArray, CArray, DArray},
                    AArrayDataLE, BArrayDataLE, CArrayDataLE, DArrayDataLE);
}

TEST(BinaryStreamInput, LittleEndianReadStruct)
{
    readAndAssertLE(std::tuple{AB_CD}, AB_CDDataLE);
}

TEST(BinaryStreamInput, BigEndianReadType)
{
    readAndAssertBE(std::tuple{A, B, C, D},
                    ADataBE, BDataBE, CDataBE, DDataBE);
}

TEST(BinaryStreamInput, BigEndianReadArray)
{
    readAndAssertBE(std::tuple{AArray, BArray, CArray, DArray},
                    AArrayDataBE, BArrayDataBE, CArrayDataBE, DArrayDataBE);
}

TEST(BinaryStreamInput, BigEndianReadStruct)
{
    readAndAssertBE(std::tuple{AB_CD}, AB_CDDataBE);
}

TEST(BinaryStreamInput, ReadStringENUTF8)
{
    if constexpr(SCPPL_CONFIG_BINARY_USE_ICU)
    {
        readStringAndAssert(ENChar8Text, "UTF-8", ENTextUTF8Data);
    }
}

TEST(BinaryStreamInput, ReadStringENASCII)
{
    if constexpr(SCPPL_CONFIG_BINARY_USE_ICU)
    {
        readStringAndAssert(ENChar8Text, "ASCII", ENTextASCIIData);
    }
}

TEST(BinaryStreamInput, ReadStringJPUTF8)
{
    if constexpr(SCPPL_CONFIG_BINARY_USE_ICU)
    {
        readStringAndAssert(JPChar8Text, "UTF-8", JPTextUTF8Data);
    }
}

TEST(BinaryStreamInput, ReadStringJPShiftJIS)
{
    if constexpr(SCPPL_CONFIG_BINARY_USE_ICU)
    {
        readStringAndAssert(JPChar8Text, "Shift-JIS", JPTextShiftJISData);
    }
}
