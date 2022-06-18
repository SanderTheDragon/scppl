// SPDX-FileCopyrightText: 2021-2022 SanderTheDragon <sanderthedragon@zoho.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <algorithm>
#include <array>
#include <bit>
#include <cstddef>
#include <functional>
#include <iosfwd>
#include <ranges>
#include <string>
#include <string_view>
#include <tuple>
#include <utility>

#include <gtest/gtest.h>

#include "scppl/binary/BinaryOutputStream.hpp"

#include "Data.hpp"
#include "Types.hpp"
#include "Utility.hpp"
#include "Values.hpp"

template<std::size_t N>
auto fromStream(std::ostringstream& stringstream)
    -> ByteArray<N>
{
    ByteArray<N> data{};

    auto string = stringstream.str();
    std::ranges::copy(std::ranges::begin(string), std::ranges::end(string),
                      std::ranges::begin(data));

    return data;
}

template<std::endian tEndian, typename... Ts, std::size_t... Ns>
requires(sizeof...(Ts) == sizeof...(Ns))
void writeAndAssert(std::tuple<Ts...> values, ByteArray<Ns>... expected)
{
    std::ostringstream stringstream{};
    scppl::BinaryOutputStream<tEndian> stream(stringstream);
    std::apply(std::bind_front(&decltype(stream)::template write<Ts...>,
                               stream),
                values);

    auto data = fromStream<(Ns + ...)>(stringstream);

    assertDataEqual(data, expected...);
}

constexpr auto writeAndAssertLE = [](auto&&... args) -> void
{
    writeAndAssert<std::endian::little>(std::forward<decltype(args)>(args)...);
};

constexpr auto writeAndAssertBE = [](auto&&... args) -> void
{
    writeAndAssert<std::endian::big>(std::forward<decltype(args)>(args)...);
};

template<typename CharT, std::size_t... Ns>
void writeStringAndAssert(std::basic_string<CharT> string,
                          std::string_view encoding,
                          ByteArray<Ns>... expected)
{
    std::ostringstream stringstream{};
    scppl::BinaryOutputStream<> stream(stringstream);
    stream.writeString<CharT>(string, encoding);

    auto data = fromStream<(Ns + ...)>(stringstream);

    assertDataEqual(data, expected...);
}

TEST(BinaryStreamOutput, LittleEndianWriteType)
{
    writeAndAssertLE(std::tuple{A, B, C, D},
                     ADataLE, BDataLE, CDataLE, DDataLE);
}

TEST(BinaryStreamOutput, LittleEndianWriteArray)
{
    writeAndAssertLE(std::tuple{AArray, BArray, CArray, DArray},
                     AArrayDataLE, BArrayDataLE, CArrayDataLE, DArrayDataLE);
}

TEST(BinaryStreamOutput, LittleEndianWriteStruct)
{
    writeAndAssertLE(std::tuple{AB_CD}, AB_CDDataLE);
}

TEST(BinaryStreamOutput, BigEndianWriteType)
{
    writeAndAssertBE(std::tuple{A, B, C, D},
                     ADataBE, BDataBE, CDataBE, DDataBE);
}

TEST(BinaryStreamOutput, BigEndianWriteArray)
{
    writeAndAssertBE(std::tuple{AArray, BArray, CArray, DArray},
                     AArrayDataBE, BArrayDataBE, CArrayDataBE, DArrayDataBE);
}

TEST(BinaryStreamOutput, BigEndianWriteStruct)
{
    writeAndAssertBE(std::tuple{AB_CD}, AB_CDDataBE);
}

TEST(BinaryStreamOutput, WriteStringENUTF8)
{
    if constexpr(SCPPL_CONFIG_BINARY_USE_ICU)
    {
        writeStringAndAssert(ENChar8Text, "UTF-8", ENTextUTF8Data);
    }
}

TEST(BinaryStreamOutput, WriteStringENASCII)
{
    if constexpr(SCPPL_CONFIG_BINARY_USE_ICU)
    {
        writeStringAndAssert(ENChar8Text, "ASCII", ENTextASCIIData);
    }
}

TEST(BinaryStreamOutput, WriteStringJPUTF8)
{
    if constexpr(SCPPL_CONFIG_BINARY_USE_ICU)
    {
        writeStringAndAssert(JPChar8Text, "UTF-8", JPTextUTF8Data);
    }
}

TEST(BinaryStreamOutput, WriteStringJPShiftJIS)
{
    if constexpr(SCPPL_CONFIG_BINARY_USE_ICU)
    {
        writeStringAndAssert(JPChar8Text, "Shift-JIS", JPTextShiftJISData);
    }
}
