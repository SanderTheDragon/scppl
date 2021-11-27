// SPDX-FileCopyrightText: 2021 SanderTheDragon <sanderthedragon@zoho.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <array>
#include <cstdint>
#include <vector>

#include <gtest/gtest.h>

#include "scppl/binary/Binary.hpp"

// NOLINTNEXTLINE: External
TEST(BinaryPack, SingleType)
{
    auto data = scppl::Binary::pack<uint16_t>(0x0123);

    ASSERT_EQ(data.at(0), 0x23);
    ASSERT_EQ(data.at(1), 0x01);
}

// NOLINTNEXTLINE: External
TEST(BinaryPack, DualType)
{
    auto data = scppl::Binary::pack<uint16_t, uint16_t>(0x0123, 0x4567);

    ASSERT_EQ(data.at(0), 0x23);
    ASSERT_EQ(data.at(1), 0x01);
    ASSERT_EQ(data.at(2), 0x67);
    ASSERT_EQ(data.at(3), 0x45);
}
