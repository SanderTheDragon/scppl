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
        if (std::filesystem::is_regular_file("/etc/xdg/user-dirs.defaults"))
            return;

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

        for (auto const& directory : { "Desktop", "Downloads", "Templates",
                                       "Public", "Documents", "Music",
                                       "Pictures", "Videos" })
        {
            std::filesystem::create_directories(scppl::FileSystem::getHome()
                                                / directory);
        }
        // GCOVR_EXCL_END
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
