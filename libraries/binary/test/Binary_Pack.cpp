// SPDX-FileCopyrightText: 2021-2022 SanderTheDragon <sanderthedragon@zoho.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <array>
#include <bit>
#include <cstddef>
#include <memory>
#include <tuple>
#include <utility>

#include <gtest/gtest.h>

#include "scppl/binary/Binary.hpp"

#include "Data.hpp"
#include "Types.hpp"
#include "Utility.hpp"
#include "Values.hpp"

template<std::endian tEndian, typename... Ts, std::size_t... Ns>
requires(sizeof...(Ts) == sizeof...(Ns))
void packAndAssert(std::tuple<Ts...> values, ByteArray<Ns>... expected)
{
    auto data = std::apply(scppl::Binary<tEndian>::template pack<Ts...>,
                           values);

    assertDataEqual(data, expected...);
}

constexpr auto packAndAssertLE = [](auto&&... args) -> void {
    packAndAssert<std::endian::little>(std::forward<decltype(args)>(args)...);
};

constexpr auto packAndAssertBE = [](auto&&... args) -> void {
    packAndAssert<std::endian::big>(std::forward<decltype(args)>(args)...);
};

TEST(BinaryPack, LittleEndianOneType)
{
    packAndAssertLE(std::tuple{A}, ADataLE);
    packAndAssertLE(std::tuple{B}, BDataLE);
    packAndAssertLE(std::tuple{C}, CDataLE);
    packAndAssertLE(std::tuple{D}, DDataLE);
}

TEST(BinaryPack, LittleEndianTwoType)
{
    packAndAssertLE(std::tuple{A, B}, ADataLE, BDataLE);
    packAndAssertLE(std::tuple{B, C}, BDataLE, CDataLE);
    packAndAssertLE(std::tuple{C, D}, CDataLE, DDataLE);
    packAndAssertLE(std::tuple{D, A}, DDataLE, ADataLE);
}

TEST(BinaryPack, LittleEndianThreeType)
{
    packAndAssertLE(std::tuple{A, B, C}, ADataLE, BDataLE, CDataLE);
    packAndAssertLE(std::tuple{B, C, D}, BDataLE, CDataLE, DDataLE);
    packAndAssertLE(std::tuple{C, D, A}, CDataLE, DDataLE, ADataLE);
    packAndAssertLE(std::tuple{D, A, B}, DDataLE, ADataLE, BDataLE);
}

TEST(BinaryPack, LittleEndianFourType)
{
    packAndAssertLE(std::tuple{A, B, C, D},
                    ADataLE, BDataLE, CDataLE, DDataLE);
    packAndAssertLE(std::tuple{B, C, D, A},
                    BDataLE, CDataLE, DDataLE, ADataLE);
    packAndAssertLE(std::tuple{C, D, A, B},
                    CDataLE, DDataLE, ADataLE, BDataLE);
    packAndAssertLE(std::tuple{D, A, B, C},
                    DDataLE, ADataLE, BDataLE, CDataLE);
}

TEST(BinaryPack, LittleEndianArray)
{
    packAndAssertLE(std::tuple{AArray}, AArrayDataLE);
    packAndAssertLE(std::tuple{BArray}, BArrayDataLE);
    packAndAssertLE(std::tuple{CArray}, CArrayDataLE);
    packAndAssertLE(std::tuple{DArray}, DArrayDataLE);
}

TEST(BinaryPack, LittleEndianStruct)
{
    if constexpr(std::endian::native == std::endian::little ||
                 SCPPL_CONFIG_BINARY_USE_PFR)
    {
        packAndAssertLE(std::tuple{AB}, ABDataLE);
        packAndAssertLE(std::tuple{CD}, CDDataLE);
    }
}

TEST(BinaryPack, LittleEndianStructStruct)
{
    if constexpr(std::endian::native == std::endian::little ||
                 SCPPL_CONFIG_BINARY_USE_PFR)
    {
        packAndAssertLE(std::tuple{AB_CD}, AB_CDDataLE);
    }
}

TEST(BinaryPack, LittleEndianStructArray)
{
    if constexpr(std::endian::native == std::endian::little ||
                 SCPPL_CONFIG_BINARY_USE_PFR)
    {
        packAndAssertLE(std::tuple{AB_CDArray}, AB_CDArrayDataLE);
    }
}

TEST(BinaryPack, LittleEndianArrayStruct)
{
    if constexpr(std::endian::native == std::endian::little ||
                 SCPPL_CONFIG_BINARY_USE_PFR)
    {
        packAndAssertLE(std::tuple{ABCDArray}, ABCDArrayDataLE);
    }
}

TEST(BinaryPack, LittleEndianArrayStructArray)
{
    if constexpr(std::endian::native == std::endian::little ||
                 SCPPL_CONFIG_BINARY_USE_PFR)
    {
        packAndAssertLE(std::tuple{ABCDArrayArray}, ABCDArrayArrayDataLE);
    }
}

TEST(BinaryPack, BigEndianOneType)
{
    packAndAssertBE(std::tuple{A}, ADataBE);
    packAndAssertBE(std::tuple{B}, BDataBE);
    packAndAssertBE(std::tuple{C}, CDataBE);
    packAndAssertBE(std::tuple{D}, DDataBE);
}

TEST(BinaryPack, BigEndianTwoType)
{
    packAndAssertBE(std::tuple{A, B}, ADataBE, BDataBE);
    packAndAssertBE(std::tuple{B, C}, BDataBE, CDataBE);
    packAndAssertBE(std::tuple{C, D}, CDataBE, DDataBE);
    packAndAssertBE(std::tuple{D, A}, DDataBE, ADataBE);
}

TEST(BinaryPack, BigEndianThreeType)
{
    packAndAssertBE(std::tuple{A, B, C}, ADataBE, BDataBE, CDataBE);
    packAndAssertBE(std::tuple{B, C, D}, BDataBE, CDataBE, DDataBE);
    packAndAssertBE(std::tuple{C, D, A}, CDataBE, DDataBE, ADataBE);
    packAndAssertBE(std::tuple{D, A, B}, DDataBE, ADataBE, BDataBE);
}

TEST(BinaryPack, BigEndianFourType)
{
    packAndAssertBE(std::tuple{A, B, C, D},
                    ADataBE, BDataBE, CDataBE, DDataBE);
    packAndAssertBE(std::tuple{B, C, D, A},
                    BDataBE, CDataBE, DDataBE, ADataBE);
    packAndAssertBE(std::tuple{C, D, A, B},
                    CDataBE, DDataBE, ADataBE, BDataBE);
    packAndAssertBE(std::tuple{D, A, B, C},
                    DDataBE, ADataBE, BDataBE, CDataBE);
}

TEST(BinaryPack, BigEndianArray)
{
    packAndAssertBE(std::tuple{AArray}, AArrayDataBE);
    packAndAssertBE(std::tuple{BArray}, BArrayDataBE);
    packAndAssertBE(std::tuple{CArray}, CArrayDataBE);
    packAndAssertBE(std::tuple{DArray}, DArrayDataBE);
}

TEST(BinaryPack, BigEndianStruct)
{
    if constexpr(std::endian::native == std::endian::big ||
                 SCPPL_CONFIG_BINARY_USE_PFR)
    {
        packAndAssertBE(std::tuple{AB}, ABDataBE);
        packAndAssertBE(std::tuple{CD}, CDDataBE);
    }
}

TEST(BinaryPack, BigEndianStructStruct)
{
    if constexpr(std::endian::native == std::endian::big ||
                 SCPPL_CONFIG_BINARY_USE_PFR)
    {
        packAndAssertBE(std::tuple{AB_CD}, AB_CDDataBE);
    }
}

TEST(BinaryPack, BigEndianStructArray)
{
    if constexpr(std::endian::native == std::endian::big ||
                 SCPPL_CONFIG_BINARY_USE_PFR)
    {
        packAndAssertBE(std::tuple{AB_CD}, AB_CDDataBE);
    }
}

TEST(BinaryPack, BigEndianArrayStruct)
{
    if constexpr(std::endian::native == std::endian::big ||
                 SCPPL_CONFIG_BINARY_USE_PFR)
    {
        packAndAssertBE(std::tuple{ABCDArray}, ABCDArrayDataBE);
    }
}

TEST(BinaryPack, BigEndianArrayStructArray)
{
    if constexpr(std::endian::native == std::endian::big ||
                 SCPPL_CONFIG_BINARY_USE_PFR)
    {
        packAndAssertBE(std::tuple{ABCDArrayArray}, ABCDArrayArrayDataBE);
    }
}
