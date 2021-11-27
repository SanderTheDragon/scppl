// SPDX-FileCopyrightText: 2021 SanderTheDragon <sanderthedragon@zoho.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <cstdint>
#include <vector>

#include <gtest/gtest.h>

#include "scppl/binary/Binary.hpp"

// NOLINTNEXTLINE: External
TEST(BinaryUnpack, SingleType)
{
    std::vector<char> data = { 0x23, 0x01 };
    auto [ a ] = scppl::Binary::unpack<uint16_t>(data);

    ASSERT_EQ(a, 0x0123);
}

// NOLINTNEXTLINE: External
TEST(BinaryUnpack, DualType)
{
    std::vector<char> data = { 0x23, 0x01, 0x67, 0x45 };
    auto [ a, b ] = scppl::Binary::unpack<uint16_t, uint16_t>(data);

    ASSERT_EQ(a, 0x0123);
    ASSERT_EQ(b, 0x4567);
}
