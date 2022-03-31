// SPDX-FileCopyrightText: 2021-2022 SanderTheDragon <sanderthedragon@zoho.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "scppl/os/Platform.hpp"
#ifdef SCPPL_OS_UNIX
#include <unistd.h>
#endif

#include <climits>
#include <cstdlib>
#include <string>

#include <gtest/gtest.h>

#include "scppl/os/Utility.hpp"

TEST(Utility, Environment)
{
    // Set a variable and try to get it
    ::setenv("SCPPL_VARIABLE", "1234", 1);
    ASSERT_STREQ(scppl::environment("SCPPL_VARIABLE").c_str(), "1234");

    // Overwrite a variable and try to get it
    ::setenv("SCPPL_VARIABLE", "12345", 1);
    ASSERT_STREQ(scppl::environment("SCPPL_VARIABLE").c_str(), "12345");

    // Do not overwrite the variable and try to get it
    ::setenv("SCPPL_VARIABLE", "123456", 0);
    ASSERT_STREQ(scppl::environment("SCPPL_VARIABLE").c_str(), "12345");
}

TEST(Utility, EnvironmentFallback)
{
    // Force fallback by getting an unset variable
    ::unsetenv("SCPPL_VARIABLE");
    ASSERT_STREQ(scppl::environment("SCPPL_VARIABLE", "1234").c_str(), "1234");
}

TEST(Utility, SetEnvironmentNoOverwrite)
{
    // Set a variable and try to get it
    scppl::setEnvironment("SCPPL_VARIABLE", "1234");
    ASSERT_STREQ(scppl::environment("SCPPL_VARIABLE").c_str(), "1234");

    // Do not overwrite the variable and try to get it
    scppl::setEnvironment("SCPPL_VARIABLE", "12345");
    ASSERT_STREQ(scppl::environment("SCPPL_VARIABLE").c_str(), "1234");
}

TEST(Utility, SetEnvironmentOverwrite)
{
    // Set a variable and try to get it
    scppl::setEnvironment("SCPPL_VARIABLE", "1234");
    ASSERT_STREQ(scppl::environment("SCPPL_VARIABLE").c_str(), "1234");

    // Overwrite a variable and try to get it
    scppl::setEnvironment("SCPPL_VARIABLE", "12345", true);
    ASSERT_STREQ(scppl::environment("SCPPL_VARIABLE").c_str(), "12345");
}

#ifdef SCPPL_OS_UNIX
TEST(Utility, SystemConfig)
{
    // Some random variables, taken from the manual page (`man sysconf`)
    ASSERT_GE(scppl::systemConfig(_SC_ARG_MAX), _POSIX_ARG_MAX);
    ASSERT_GE(scppl::systemConfig(_SC_LOGIN_NAME_MAX), _POSIX_LOGIN_NAME_MAX);
    ASSERT_GE(scppl::systemConfig(_SC_OPEN_MAX), _POSIX_OPEN_MAX);
}

TEST(Utility, SystemConfigFallback)
{
    // Force fallback by getting a non existing variable (`-1`)
    ASSERT_EQ(scppl::systemConfig(-1, 1234), 1234);
}
#endif
