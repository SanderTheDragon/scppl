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

void ensureDirectoriesExist(std::vector<std::filesystem::path> const& paths)
{
    for (auto const& path : paths)
    {
        if (!std::filesystem::is_directory(path))
            std::filesystem::create_directories(path); // GCOVR_EXCL_LINE
    }
}

TEST(StandardPaths, GetConfigDirectories)
{
#ifdef SCPPL_OS_LINUX
    // Make sure "XDG_CONFIG_DIRS" and "XDG_CONFIG_HOME" are set to existing
    // (non-default) paths
    ::setenv("XDG_CONFIG_DIRS", "/etc", 1);
    ::setenv("XDG_CONFIG_HOME", "/home", 1);
#endif

    assertStandardPaths(scppl::StandardPaths::getConfigDirectories(),
                        scppl::StandardPaths::ConfigDirectory);
}

#ifdef SCPPL_OS_LINUX
TEST(StandardPaths, GetConfigDirectoriesFallback)
{
    // Make sure "XDG_CONFIG_DIRS" and "XDG_CONFIG_HOME" are unset and the
    // default directories exist
    ::unsetenv("XDG_CONFIG_HOME");
    ::unsetenv("XDG_CONFIG_DIRS");

    ensureDirectoriesExist({ "/etc/xdg",
                             scppl::FileSystem::getHome() / ".config" });

    assertStandardPaths(scppl::StandardPaths::getConfigDirectories(),
                        scppl::StandardPaths::ConfigDirectory);
}
#endif

TEST(StandardPaths, GetDataDirectories)
{
#ifdef SCPPL_OS_LINUX
    // Make sure "XDG_DATA_DIRS" and "XDG_DATA_HOME" are set to existing
    // (non-default) paths
    ::setenv("XDG_DATA_DIRS", "/usr", 1);
    ::setenv("XDG_DATA_HOME", "/home", 1);
#endif

    assertStandardPaths(scppl::StandardPaths::getDataDirectories(),
                        scppl::StandardPaths::DataDirectory);
}

#ifdef SCPPL_OS_LINUX
TEST(StandardPaths, GetDataDirectoriesFallback)
{
    // Make sure "XDG_DATA_HOME" and "XDG_DATA_DIRS" are unset and the default
    // directories exist
    ::unsetenv("XDG_DATA_DIRS");
    ::unsetenv("XDG_DATA_HOME");

    ensureDirectoriesExist({ "/usr/share", "/usr/local/share",
                             scppl::FileSystem::getHome() / ".config" });

    assertStandardPaths(scppl::StandardPaths::getDataDirectories(),
                        scppl::StandardPaths::DataDirectory);
}
#endif

TEST(StandardPaths, GetCacheDirectory)
{
#ifdef SCPPL_OS_LINUX
    // Make sure "XDG_CACHE_HOME" is set to an existing (non-default) path
    ::setenv("XDG_CACHE_HOME", "/home", 1);
#endif

    assertStandardPaths({ scppl::StandardPaths::getCacheDirectory() },
                        scppl::StandardPaths::CacheDirectory);
}

#ifdef SCPPL_OS_LINUX
TEST(StandardPaths, GetCacheDirectoryFallback)
{
    // Make sure "XDG_CACHE_HOME" is unset and the default directory exists
    ::unsetenv("XDG_CACHE_HOME");

    ensureDirectoriesExist({ scppl::FileSystem::getHome() / ".cache" });

    assertStandardPaths({ scppl::StandardPaths::getCacheDirectory() },
                        scppl::StandardPaths::CacheDirectory);
}
#endif

TEST(StandardPaths, GetStateDirectory)
{
#ifdef SCPPL_OS_LINUX
    // Make sure "XDG_STATE_HOME" is set to an existing (non-default) path
    ::setenv("XDG_STATE_HOME", "/home", 1);
#endif

    assertStandardPaths({ scppl::StandardPaths::getStateDirectory() },
                        scppl::StandardPaths::StateDirectory);
}

#ifdef SCPPL_OS_LINUX
TEST(StandardPaths, GetStateDirectoryFallback)
{
    // Make sure "XDG_STATE_HOME" is unset and the default directory exists
    ::unsetenv("XDG_STATE_HOME");

    ensureDirectoriesExist({ scppl::FileSystem::getHome() / ".local/state" });

    assertStandardPaths({ scppl::StandardPaths::getStateDirectory() },
                        scppl::StandardPaths::StateDirectory);
}
#endif

TEST(StandardPaths, GetRuntimeDirectory)
{
#ifdef SCPPL_OS_LINUX
    // Make sure "XDG_CACHE_HOME" is set to an existing (non-default) path
    ::setenv("XDG_RUNTIME_DIR", "/tmp", 1);
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
