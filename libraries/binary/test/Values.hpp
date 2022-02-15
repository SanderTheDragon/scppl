// SPDX-FileCopyrightText: 2021-2022 SanderTheDragon <sanderthedragon@zoho.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef TEST_VALUES_HPP_
#define TEST_VALUES_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <ranges>

#include <gtest/gtest.h>

#include "Types.hpp"
#include "Utility.hpp"

// Binary_*
constexpr A_t A = 0x01;
constexpr B_t B = 0x01'23;
constexpr C_t C = 0x01'23'45'67;
constexpr D_t D = 0x01'23'45'67'89'AB'CD'EF;

constexpr AArray_t<1> AArray{A};
constexpr BArray_t<2> BArray{B, B};
constexpr CArray_t<3> CArray{C, C, C};
constexpr DArray_t<4> DArray{D, D, D, D};

constexpr AB_t AB{A, B};
constexpr CD_t CD{C, D};

constexpr AB_CD_t AB_CD{AB, CD};

constexpr AB_CDArray_t<2> AB_CDArray{AB_CD, AB_CD};

constexpr ABCDArray_t<1, 2, 3, 4> ABCDArray{AArray, BArray, CArray, DArray};

constexpr ABCDArrayArray_t<2, 1, 2, 3, 4> ABCDArrayArray{ABCDArray, ABCDArray};

// BinaryString_*
static std::basic_string<char8_t> const ENChar8Text{u8"TestText"};
static std::basic_string<char8_t> const JPChar8Text{u8"テストテキスト"};
static std::basic_string<char16_t> const ENChar16Text{u"TestText"};
static std::basic_string<char16_t> const JPChar16Text{u"テストテキスト"};
static std::basic_string<char32_t> const ENChar32Text{U"TestText"};
static std::basic_string<char32_t> const JPChar32Text{U"テストテキスト"};

#endif
