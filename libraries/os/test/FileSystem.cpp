// SPDX-FileCopyrightText: 2021-2022 SanderTheDragon <sanderthedragon@zoho.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <cstdlib>
#include <filesystem>
#include <string>

#include <gtest/gtest.h>

#include "scppl/os/FileSystem.hpp"
#include "scppl/os/Platform.hpp"

TEST(FileSystem, GetHome)
{
#ifdef SCPPL_OS_UNIX
    // Not an user home directory, but enough to test whether getting the "HOME"
    // environment variable works
    ::setenv("HOME", "/home", 0);

    // Also create the directory if it does not exist
    std::filesystem::create_directory("/home");
#endif

    auto path = scppl::FileSystem::getHome();
    ASSERT_TRUE(std::filesystem::is_directory(path));
}

#ifdef SCPPL_OS_UNIX
TEST(FileSystem, GetHomeUnixPWD)
{
    // Make sure "HOME" is unset
    ::unsetenv("HOME");

    auto path = scppl::FileSystem::getHome();
    ASSERT_TRUE(std::filesystem::is_directory(path));
}
#endif

TEST(FileSystem, GetTemporaryDirectory)
{
    auto path = scppl::FileSystem::getTemporaryDirectory();
    ASSERT_TRUE(std::filesystem::is_directory(path));
}

TEST(FileSystem, GetTemporaryDirectoryPrefixed)
{
    auto path = scppl::FileSystem::getTemporaryDirectory("prefix");
    ASSERT_TRUE(std::filesystem::is_directory(path));
    ASSERT_TRUE(path.string().find("prefix") != std::string::npos);
}
