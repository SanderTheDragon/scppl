// SPDX-FileCopyrightText: 2021-2022 SanderTheDragon <sanderthedragon@zoho.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "scppl/os/FileSystem.hpp"

#include "scppl/os/Platform.hpp"

#ifdef SCPPL_OS_UNIX
#include <pwd.h>
#include <unistd.h>
#endif

#include <stdexcept>

#ifdef SCPPL_OS_UNIX
#include <cstdlib>
#include <string>
#include <vector>
#endif

#include "scppl/os/Utility.hpp"

namespace scppl {

auto FileSystem::getHome()
    -> Path
{
#ifdef SCPPL_OS_UNIX
    Path home = environment("HOME");
    if (!home.empty() && std::filesystem::is_directory(home))
        return home;

    long bufferSize = systemConfig(_SC_GETPW_R_SIZE_MAX, 0x4000);
    std::vector<char> buffer(bufferSize);

    struct ::passwd pwd{};
    struct ::passwd* result = nullptr;
    ::getpwuid_r(::getuid(), &pwd, buffer.data(), bufferSize, &result);
    if (result != nullptr)
    {
        if constexpr(SCPPL_CONFIG_OS_SAVE_PWD_HOME)
            setEnvironment("HOME", result->pw_dir, true);

        return result->pw_dir;
    }

    throw std::runtime_error("Unable to get the home directory");
#else
    throw std::runtime_error(SCPPL_OS_NAME " is not supported (yet)");
#endif
}

auto FileSystem::getTemporaryDirectory(std::string_view prefix)
    -> Path
{
#ifdef SCPPL_OS_UNIX
    // TODO: `std::format`, when GCC supports it
    std::string subdirectory{prefix};
    subdirectory += "XXXXXX";
    std::string tmp =
        (std::filesystem::temp_directory_path() / subdirectory).string();

    if (char* directory = ::mkdtemp(tmp.data()); directory != nullptr)
        return directory;

    throw std::runtime_error("Unable to create a temporary directory");
#else
    throw std::runtime_error(SCPPL_OS_NAME " is not supported (yet)");
#endif
}

}
