// SPDX-FileCopyrightText: 2021-2022 SanderTheDragon <sanderthedragon@zoho.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "scppl/os/Platform.hpp"

#ifdef SCPPL_OS_LINUX
#include <filesystem>
#include <fstream>
#include <initializer_list>
#endif

#include <gtest/gtest.h>

#include "scppl/os/FileSystem.hpp"

class Environment : public testing::Environment
{
public:
    void SetUp() override
    {
#ifdef SCPPL_OS_LINUX
        // GCOVR_EXCL_START
        auto createDirectories = []() -> void
        {
            for (auto const& directory : { "Desktop", "Downloads", "Templates",
                                           "Public", "Documents", "Music",
                                           "Pictures", "Videos" })
            {
                std::filesystem::create_directories(scppl::FileSystem::getHome()
                                                    / directory);
            }
        };
        // GCOVR_EXCL_STOP

        if (!std::filesystem::is_regular_file("/etc/xdg/user-dirs.defaults"))
        {
            // GCOVR_EXCL_START
            std::filesystem::create_directories("/etc/xdg");
            std::ofstream stream("/etc/xdg/user-dirs.defaults");
            stream << "DESKTOP=Desktop" << std::endl
                   << "DOWNLOAD=Downloads" << std::endl
                   << "TEMPLATES=Templates" << std::endl
                   << "PUBLICSHARE=Public" << std::endl
                   << "DOCUMENTS=Documents" << std::endl
                   << "MUSIC=Music" << std::endl
                   << "PICTURES=Pictures" << std::endl
                   << "VIDEOS=Videos" << std::endl;

            createDirectories();
            // GCOVR_EXCL_STOP
        }

        if (!std::filesystem::is_regular_file(scppl::FileSystem::getHome()
                                              / ".config/user-dirs.dirs"))
        {
            // GCOVR_EXCL_START
            std::filesystem::create_directories(scppl::FileSystem::getHome()
                                                / ".config");
            std::ofstream stream(scppl::FileSystem::getHome()
                                 / ".config/user-dirs.dirs");
            stream << "XDG_DESKTOP_DIR=\"$HOME/Desktop\"" << std::endl
                   << "XDG_DOWNLOAD_DIR=\"$HOME/Downloads\"" << std::endl
                   << "XDG_TEMPLATES_DIR=\"$HOME/Templates\"" << std::endl
                   << "XDG_PUBLICSHARE_DIR=\"$HOME/Public\"" << std::endl
                   << "XDG_DOCUMENTS_DIR=\"$HOME/Documents\"" << std::endl
                   << "XDG_MUSIC_DIR=\"$HOME/Music\"" << std::endl
                   << "XDG_PICTURES_DIR=\"$HOME/Pictures\"" << std::endl
                   << "XDG_VIDEOS_DIR=\"$HOME/Videos\"" << std::endl;

            createDirectories();
            // GCOVR_EXCL_STOP
        }
#endif
    }
};

auto main(int argc, char* argv[])
    -> int
{
    testing::InitGoogleTest(&argc, argv);

    // NOLINTNEXTLINE(cppcoreguidelines-owning-memory): `new` is required here
    testing::AddGlobalTestEnvironment(new Environment());

    return RUN_ALL_TESTS();
}
