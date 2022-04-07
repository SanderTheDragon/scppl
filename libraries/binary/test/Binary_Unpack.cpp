// SPDX-FileCopyrightText: 2021-2022 SanderTheDragon <sanderthedragon@zoho.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <array>
#include <bit>
#include <cstddef>
#include <tuple>
#include <utility>
#include <vector>

#include <gtest/gtest.h>

#include "scppl/binary/Binary.hpp"

#include "Data.hpp"
#include "Types.hpp"
#include "Utility.hpp"
#include "Values.hpp"

template<std::endian tEndian, typename... Ts, std::size_t... Ns>
requires(sizeof...(Ts) == sizeof...(Ns))
void unpackAndAssert(std::tuple<Ts...> expected, ByteArray<Ns>... datas)
{
    auto data = combineArrays(datas...);
    auto values = scppl::Binary<tEndian>::template unpack<Ts...>(data);

    assertValuesEqual(values, expected);
}

constexpr auto unpackAndAssertLE = [](auto&&... args) -> void {
    unpackAndAssert<std::endian::little>(std::forward<decltype(args)>(args)...);
};

constexpr auto unpackAndAssertBE = [](auto&&... args) -> void {
    unpackAndAssert<std::endian::big>(std::forward<decltype(args)>(args)...);
};

TEST(BinaryUnpack, LittleEndianOneType)
{
    unpackAndAssertLE(std::tuple{A}, ADataLE);
    unpackAndAssertLE(std::tuple{B}, BDataLE);
    unpackAndAssertLE(std::tuple{C}, CDataLE);
    unpackAndAssertLE(std::tuple{D}, DDataLE);
}

TEST(BinaryUnpack, LittleEndianTwoType)
{
    unpackAndAssertLE(std::tuple{A, B}, ADataLE, BDataLE);
    unpackAndAssertLE(std::tuple{B, C}, BDataLE, CDataLE);
    unpackAndAssertLE(std::tuple{C, D}, CDataLE, DDataLE);
    unpackAndAssertLE(std::tuple{D, A}, DDataLE, ADataLE);
}

TEST(BinaryUnpack, LittleEndianThreeType)
{
    unpackAndAssertLE(std::tuple{A, B, C}, ADataLE, BDataLE, CDataLE);
    unpackAndAssertLE(std::tuple{B, C, D}, BDataLE, CDataLE, DDataLE);
    unpackAndAssertLE(std::tuple{C, D, A}, CDataLE, DDataLE, ADataLE);
    unpackAndAssertLE(std::tuple{D, A, B}, DDataLE, ADataLE, BDataLE);
}

TEST(BinaryUnpack, LittleEndianFourType)
{
    unpackAndAssertLE(std::tuple{A, B, C, D},
                      ADataLE, BDataLE, CDataLE, DDataLE);
    unpackAndAssertLE(std::tuple{B, C, D, A},
                      BDataLE, CDataLE, DDataLE, ADataLE);
    unpackAndAssertLE(std::tuple{C, D, A, B},
                      CDataLE, DDataLE, ADataLE, BDataLE);
    unpackAndAssertLE(std::tuple{D, A, B, C},
                      DDataLE, ADataLE, BDataLE, CDataLE);
}

TEST(BinaryUnpack, LittleEndianArray)
{
    unpackAndAssertLE(std::tuple{AArray}, AArrayDataLE);
    unpackAndAssertLE(std::tuple{BArray}, BArrayDataLE);
    unpackAndAssertLE(std::tuple{CArray}, CArrayDataLE);
    unpackAndAssertLE(std::tuple{DArray}, DArrayDataLE);
}

TEST(BinaryUnpack, LittleEndianStruct)
{
    if constexpr(std::endian::native == std::endian::little ||
                 SCPPL_CONFIG_BINARY_USE_PFR)
    {
        unpackAndAssertLE(std::tuple{AB}, ABDataLE);
        unpackAndAssertLE(std::tuple{CD}, CDDataLE);
    }
}

TEST(BinaryUnpack, LittleEndianStructStruct)
{
    if constexpr(std::endian::native == std::endian::little ||
                 SCPPL_CONFIG_BINARY_USE_PFR)
    {
        unpackAndAssertLE(std::tuple{AB_CD}, AB_CDDataLE);
    }
}

TEST(BinaryUnpack, LittleEndianStructArray)
{
    if constexpr(std::endian::native == std::endian::little ||
                 SCPPL_CONFIG_BINARY_USE_PFR)
    {
        unpackAndAssertLE(std::tuple{AB_CDArray}, AB_CDArrayDataLE);
    }
}

TEST(BinaryUnpack, LittleEndianArrayStruct)
{
    if constexpr(std::endian::native == std::endian::little ||
                 SCPPL_CONFIG_BINARY_USE_PFR)
    {
        unpackAndAssertLE(std::tuple{ABCDArray}, ABCDArrayDataLE);
    }
}

TEST(BinaryUnpack, LittleEndianArrayStructArray)
{
    if constexpr(std::endian::native == std::endian::little ||
                 SCPPL_CONFIG_BINARY_USE_PFR)
    {
        unpackAndAssertLE(std::tuple{ABCDArrayArray}, ABCDArrayArrayDataLE);
    }
}

TEST(BinaryUnpack, BigEndianOneType)
{
    unpackAndAssertBE(std::tuple{A}, ADataBE);
    unpackAndAssertBE(std::tuple{B}, BDataBE);
    unpackAndAssertBE(std::tuple{C}, CDataBE);
    unpackAndAssertBE(std::tuple{D}, DDataBE);
}

TEST(BinaryUnpack, BigEndianTwoType)
{
    unpackAndAssertBE(std::tuple{A, B}, ADataBE, BDataBE);
    unpackAndAssertBE(std::tuple{B, C}, BDataBE, CDataBE);
    unpackAndAssertBE(std::tuple{C, D}, CDataBE, DDataBE);
    unpackAndAssertBE(std::tuple{D, A}, DDataBE, ADataBE);
}

TEST(BinaryUnpack, BigEndianThreeType)
{
    unpackAndAssertBE(std::tuple{A, B, C}, ADataBE, BDataBE, CDataBE);
    unpackAndAssertBE(std::tuple{B, C, D}, BDataBE, CDataBE, DDataBE);
    unpackAndAssertBE(std::tuple{C, D, A}, CDataBE, DDataBE, ADataBE);
    unpackAndAssertBE(std::tuple{D, A, B}, DDataBE, ADataBE, BDataBE);
}

TEST(BinaryUnpack, BigEndianFourType)
{
    unpackAndAssertBE(std::tuple{A, B, C, D},
                      ADataBE, BDataBE, CDataBE, DDataBE);
    unpackAndAssertBE(std::tuple{B, C, D, A},
                      BDataBE, CDataBE, DDataBE, ADataBE);
    unpackAndAssertBE(std::tuple{C, D, A, B},
                      CDataBE, DDataBE, ADataBE, BDataBE);
    unpackAndAssertBE(std::tuple{D, A, B, C},
                      DDataBE, ADataBE, BDataBE, CDataBE);
}

TEST(BinaryUnpack, BigEndianArray)
{
    unpackAndAssertBE(std::tuple{AArray}, AArrayDataBE);
    unpackAndAssertBE(std::tuple{BArray}, BArrayDataBE);
    unpackAndAssertBE(std::tuple{CArray}, CArrayDataBE);
    unpackAndAssertBE(std::tuple{DArray}, DArrayDataBE);
}

TEST(BinaryUnpack, BigEndianStruct)
{
    if constexpr(std::endian::native == std::endian::big ||
                 SCPPL_CONFIG_BINARY_USE_PFR)
    {
        unpackAndAssertBE(std::tuple{AB}, ABDataBE);
        unpackAndAssertBE(std::tuple{CD}, CDDataBE);
    }
}

TEST(BinaryUnpack, BigEndianStructStruct)
{
    if constexpr(std::endian::native == std::endian::big ||
                 SCPPL_CONFIG_BINARY_USE_PFR)
    {
        unpackAndAssertBE(std::tuple{AB_CD}, AB_CDDataBE);
    }
}

TEST(BinaryUnpack, BigEndianStructArray)
{
    if constexpr(std::endian::native == std::endian::big ||
                 SCPPL_CONFIG_BINARY_USE_PFR)
    {
        unpackAndAssertBE(std::tuple{AB_CD}, AB_CDDataBE);
    }
}

TEST(BinaryUnpack, BigEndianArrayStruct)
{
    if constexpr(std::endian::native == std::endian::big ||
                 SCPPL_CONFIG_BINARY_USE_PFR)
    {
        unpackAndAssertBE(std::tuple{ABCDArray}, ABCDArrayDataBE);
    }
}

TEST(BinaryUnpack, BigEndianArrayStructArray)
{
    if constexpr(std::endian::native == std::endian::big ||
                 SCPPL_CONFIG_BINARY_USE_PFR)
    {
        unpackAndAssertBE(std::tuple{ABCDArrayArray}, ABCDArrayArrayDataBE);
    }
}
