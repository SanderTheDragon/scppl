// SPDX-FileCopyrightText: 2021-2022 SanderTheDragon <sanderthedragon@zoho.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <cstdlib>
#include <memory>
#include <string>
#include <vector>

#include <gtest/gtest.h>

#include "scppl/os/Platform.hpp"
#include "scppl/os/String.hpp"

TEST(String, SplitCharacter)
{
    auto parts = scppl::String::split("A:B:C:D:E", ':');

    ASSERT_EQ(parts.size(), 5);
    ASSERT_STREQ(parts.at(0).c_str(), "A");
    ASSERT_STREQ(parts.at(1).c_str(), "B");
    ASSERT_STREQ(parts.at(2).c_str(), "C");
    ASSERT_STREQ(parts.at(3).c_str(), "D");
    ASSERT_STREQ(parts.at(4).c_str(), "E");
}

TEST(String, SplitString)
{
    auto parts = scppl::String::split("A:-:B:-:C:-:D:-:E", ":-:");

    ASSERT_EQ(parts.size(), 5);
    ASSERT_STREQ(parts.at(0).c_str(), "A");
    ASSERT_STREQ(parts.at(1).c_str(), "B");
    ASSERT_STREQ(parts.at(2).c_str(), "C");
    ASSERT_STREQ(parts.at(3).c_str(), "D");
    ASSERT_STREQ(parts.at(4).c_str(), "E");
}

TEST(String, Expand)
{
#ifdef SCPPL_OS_UNIX
    ::setenv("VARIABLE_1", "Variable 1", 1);
    ::setenv("VALUE_1", "Value 1", 1);

    auto expanded =
        scppl::String::expand("The value of $VARIABLE_1 is ${VALUE_1}");

    ASSERT_STREQ(expanded.c_str(),
                 "The value of Variable 1 is Value 1");
#endif
}
