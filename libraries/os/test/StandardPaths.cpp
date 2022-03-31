// SPDX-FileCopyrightText: 2021-2022 SanderTheDragon <sanderthedragon@zoho.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <cstdlib>
#include <filesystem>
#include <vector>

#include <gtest/gtest.h>

#include "scppl/os/FileSystem.hpp"
#include "scppl/os/Platform.hpp"
#include "scppl/os/StandardPaths.hpp"

void assertStandardPaths(std::vector<std::filesystem::path> const& paths,
                         scppl::StandardPaths::DirectoryType directoryType)
{
    auto typePaths = scppl::StandardPaths::getDirectories(directoryType);

    for (std::size_t i = 0; i < paths.size(); ++i)
    {
        ASSERT_TRUE(std::filesystem::is_directory(paths.at(i)));
        ASSERT_EQ(paths.at(i), typePaths.at(i));
    }
}

TEST(StandardPaths, GetConfigDirectories)
{
#ifdef SCPPL_OS_LINUX
    // Make sure "XDG_CONFIG_HOME" and "XDG_CONFIG_DIRS" are set
    ::setenv("XDG_CONFIG_HOME",
             (scppl::FileSystem::getHome() / ".cache").c_str(), 0);
#endif

    assertStandardPaths(scppl::StandardPaths::getConfigDirectories(),
                        scppl::StandardPaths::ConfigDirectory);
}

#ifdef SCPPL_OS_LINUX
TEST(StandardPaths, GetConfigDirectoriesFallback)
{
    // Make sure "XDG_CONFIG_HOME" and "XDG_CONFIG_DIRS" is unset
    ::unsetenv("XDG_CONFIG_HOME");
    ::unsetenv("XDG_CONFIG_DIRS");

    assertStandardPaths(scppl::StandardPaths::getConfigDirectories(),
                        scppl::StandardPaths::ConfigDirectory);
}
#endif

TEST(StandardPaths, GetDataDirectories)
{
#ifdef SCPPL_OS_LINUX
    // Make sure "XDG_CACHE_HOME" is set
    ::setenv("XDG_CACHE_HOME",
             (scppl::FileSystem::getHome() / ".cache").c_str(), 0);
#endif

    assertStandardPaths(scppl::StandardPaths::getDataDirectories(),
                        scppl::StandardPaths::DataDirectory);
}

#ifdef SCPPL_OS_LINUX
TEST(StandardPaths, GetDataDirectoriesFallback)
{
    // Make sure "XDG_DATA_HOME" and "XDG_DATA_DIRS" is unset
    ::unsetenv("XDG_DATA_HOME");
    ::unsetenv("XDG_DATA_DIRS");

    assertStandardPaths(scppl::StandardPaths::getDataDirectories(),
                        scppl::StandardPaths::DataDirectory);
}
#endif

TEST(StandardPaths, GetCacheDirectory)
{
#ifdef SCPPL_OS_LINUX
    // Make sure "XDG_CACHE_HOME" is set
    ::setenv("XDG_CACHE_HOME",
             (scppl::FileSystem::getHome() / ".cache").c_str(), 0);
#endif

    assertStandardPaths({ scppl::StandardPaths::getCacheDirectory() },
                        scppl::StandardPaths::CacheDirectory);
}

#ifdef SCPPL_OS_LINUX
TEST(StandardPaths, GetCacheDirectoryFallback)
{
    // Make sure "XDG_CACHE_HOME" is unset
    ::unsetenv("XDG_CACHE_HOME");

    assertStandardPaths({ scppl::StandardPaths::getCacheDirectory() },
                        scppl::StandardPaths::CacheDirectory);
}
#endif

TEST(StandardPaths, GetRuntimeDirectory)
{
#ifdef SCPPL_OS_LINUX
    // Make sure "XDG_RUNTIME_DIR" is set (not a runtime directory, but good
    // enough to test)
    ::setenv("XDG_RUNTIME_DIR", "/etc", 0);
#endif

    assertStandardPaths({ scppl::StandardPaths::getRuntimeDirectory() },
                        scppl::StandardPaths::RuntimeDirectory);
}

#ifdef SCPPL_OS_LINUX
TEST(StandardPaths, GetRuntimeDirectoryFallback)
{
    // Make sure "XDG_RUNTIME_DIR" is unset
    ::unsetenv("XDG_RUNTIME_DIR");

    assertStandardPaths({ scppl::StandardPaths::getRuntimeDirectory() },
                        scppl::StandardPaths::RuntimeDirectory);
}
#endif

TEST(StandardPaths, GetStateDirectory)
{
#ifdef SCPPL_OS_LINUX
    ::setenv("XDG_CACHE_HOME",
             (scppl::FileSystem::getHome() / ".cache").c_str(), 0);
#endif

    assertStandardPaths({ scppl::StandardPaths::getStateDirectory() },
                        scppl::StandardPaths::StateDirectory);
}

#ifdef SCPPL_OS_LINUX
TEST(StandardPaths, GetStateDirectoryFallback)
{
    // Make sure "XDG_STATE_HOME" is unset
    ::unsetenv("XDG_STATE_HOME");

    assertStandardPaths({ scppl::StandardPaths::getStateDirectory() },
                        scppl::StandardPaths::StateDirectory);
}
#endif

TEST(StandardPaths, GetDesktopDirectory)
{
    assertStandardPaths({ scppl::StandardPaths::getDesktopDirectory() },
                        scppl::StandardPaths::DesktopDirectory);
}

TEST(StandardPaths, GetDocumentsDirectory)
{
    assertStandardPaths({ scppl::StandardPaths::getDocumentsDirectory() },
                        scppl::StandardPaths::DocumentsDirectory);
}

TEST(StandardPaths, GetDownloadDirectory)
{
    assertStandardPaths({ scppl::StandardPaths::getDownloadDirectory() },
                        scppl::StandardPaths::DownloadDirectory);
}

TEST(StandardPaths, GetMusicDirectory)
{
    assertStandardPaths({ scppl::StandardPaths::getMusicDirectory() },
                        scppl::StandardPaths::MusicDirectory);
}

TEST(StandardPaths, GetPicturesDirectory)
{
    assertStandardPaths({ scppl::StandardPaths::getPicturesDirectory() },
                        scppl::StandardPaths::PicturesDirectory);
}

TEST(StandardPaths, GetPublicShareDirectory)
{
    assertStandardPaths({ scppl::StandardPaths::getPublicShareDirectory() },
                        scppl::StandardPaths::PublicShareDirecotry);
}

TEST(StandardPaths, GetTemplatesDirectory)
{
    assertStandardPaths({ scppl::StandardPaths::getTemplatesDirectory() },
                        scppl::StandardPaths::TemplatesDirectory);
}

TEST(StandardPaths, GetVideosDirectory)
{
    assertStandardPaths({ scppl::StandardPaths::getVideosDirectory() },
                        scppl::StandardPaths::VideosDirectory);
}
