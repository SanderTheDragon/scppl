// SPDX-FileCopyrightText: 2021-2022 SanderTheDragon <sanderthedragon@zoho.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <algorithm>
#include <array>
#include <bit>
#include <cstddef>
#include <functional>
#include <iosfwd>
#include <memory>
#include <ranges>
#include <tuple>
#include <utility>

#include <gtest/gtest.h>

#include "scppl/binary/BinaryStream.hpp"

#include "Data.hpp"
#include "Types.hpp"
#include "Utility.hpp"
#include "Values.hpp"

template<std::endian tEndian, typename... Ts, std::size_t... Ns>
requires(sizeof...(Ts) == sizeof...(Ns))
void writeAndAssert(std::tuple<Ts...> values, ByteArray<Ns>... expected)
{
    std::ostringstream stringstream{};

    scppl::BinaryOutputStream<tEndian> stream(stringstream);
    std::apply(std::bind_front(&decltype(stream)::template write<Ts...>,
                               stream),
                values);

    auto string = stringstream.str();

    ByteArray<(Ns + ...)> data{};

    std::ranges::copy(std::ranges::begin(string), std::ranges::end(string),
                      std::ranges::begin(data));

    assertDataEqual(data, expected...);
}

constexpr auto writeAndAssertLE = [](auto&&... args) -> void {
    writeAndAssert<std::endian::little>(std::forward<decltype(args)>(args)...);
};

constexpr auto writeAndAssertBE = [](auto&&... args) -> void {
    writeAndAssert<std::endian::big>(std::forward<decltype(args)>(args)...);
};

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
