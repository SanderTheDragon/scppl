// SPDX-FileCopyrightText: 2021-2022 SanderTheDragon <sanderthedragon@zoho.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef TEST_DATA_HPP_
#define TEST_DATA_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <ranges>

#include <gtest/gtest.h>

#include "Values.hpp"
#include "Utility.hpp"

// Little-endian
constexpr ByteArray<sizeof(A)> ADataLE{'\x01'};
constexpr ByteArray<sizeof(B)> BDataLE{'\x23', '\x01'};
constexpr ByteArray<sizeof(C)> CDataLE{'\x67', '\x45', '\x23', '\x01'};
constexpr ByteArray<sizeof(D)> DDataLE{'\xEF', '\xCD', '\xAB', '\x89',
                                       '\x67', '\x45', '\x23', '\x01'};

constexpr ByteArray<sizeof(AArray)> AArrayDataLE =
    combineArrays(ADataLE);
constexpr ByteArray<sizeof(BArray)> BArrayDataLE =
    combineArrays(BDataLE, BDataLE);
constexpr ByteArray<sizeof(CArray)> CArrayDataLE =
    combineArrays(CDataLE, CDataLE, CDataLE);
constexpr ByteArray<sizeof(DArray)> DArrayDataLE =
    combineArrays(DDataLE, DDataLE, DDataLE, DDataLE);

constexpr ByteArray<sizeof(AB)> ABDataLE = combineArrays(ADataLE, BDataLE);
constexpr ByteArray<sizeof(CD)> CDDataLE = combineArrays(CDataLE, DDataLE);

constexpr ByteArray<sizeof(AB_CD)> AB_CDDataLE =
    combineArrays(ABDataLE, CDDataLE);

constexpr ByteArray<sizeof(AB_CDArray)> AB_CDArrayDataLE =
    combineArrays(AB_CDDataLE, AB_CDDataLE);

constexpr ByteArray<sizeof(ABCDArray)> ABCDArrayDataLE =
    combineArrays(AArrayDataLE, BArrayDataLE, CArrayDataLE, DArrayDataLE);

constexpr ByteArray<sizeof(ABCDArrayArray)> ABCDArrayArrayDataLE =
    combineArrays(ABCDArrayDataLE, ABCDArrayDataLE);

// Big-endian
constexpr ByteArray<sizeof(A)> ADataBE{'\x01'};
constexpr ByteArray<sizeof(B)> BDataBE{'\x01', '\x23'};
constexpr ByteArray<sizeof(C)> CDataBE{'\x01', '\x23', '\x45', '\x67'};
constexpr ByteArray<sizeof(D)> DDataBE{'\x01', '\x23', '\x45', '\x67',
                                       '\x89', '\xAB', '\xCD', '\xEF'};

constexpr ByteArray<sizeof(AArray)> AArrayDataBE =
    combineArrays(ADataBE);
constexpr ByteArray<sizeof(BArray)> BArrayDataBE =
    combineArrays(BDataBE, BDataBE);
constexpr ByteArray<sizeof(CArray)> CArrayDataBE =
    combineArrays(CDataBE, CDataBE, CDataBE);
constexpr ByteArray<sizeof(DArray)> DArrayDataBE =
    combineArrays(DDataBE, DDataBE, DDataBE, DDataBE);

constexpr ByteArray<sizeof(AB)> ABDataBE = combineArrays(ADataBE, BDataBE);
constexpr ByteArray<sizeof(CD)> CDDataBE = combineArrays(CDataBE, DDataBE);

constexpr ByteArray<sizeof(AB_CD)> AB_CDDataBE =
    combineArrays(ABDataBE, CDDataBE);

constexpr ByteArray<sizeof(AB_CDArray)> AB_CDArrayDataBE =
    combineArrays(AB_CDDataBE, AB_CDDataBE);

constexpr ByteArray<sizeof(ABCDArray)> ABCDArrayDataBE =
    combineArrays(AArrayDataBE, BArrayDataBE, CArrayDataBE, DArrayDataBE);

constexpr ByteArray<sizeof(ABCDArrayArray)> ABCDArrayArrayDataBE =
    combineArrays(ABCDArrayDataBE, ABCDArrayDataBE);

#endif
