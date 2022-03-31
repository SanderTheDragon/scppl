// SPDX-FileCopyrightText: 2021-2022 SanderTheDragon <sanderthedragon@zoho.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef SCPPL_OS_FILESYSTEM_HPP_
#define SCPPL_OS_FILESYSTEM_HPP_

#include <filesystem>
#include <string_view>

namespace scppl {

class FileSystem
{
public:
    /// A simple alias for a `std::filesystem::path`.
    using Path = std::filesystem::path;

    /**
     * @brief Get the path to the home directory of the current user.
     *
     * @details On UNIX based systems, first `$HOME` is tried, if it is not set,
     *          then the password file is used.
     *
     *          If `SCPPL_CONFIG_OS_SAVE_PWD_HOME` is not 0, then the result
     *          from the password file will be saved as `$HOME`.
     *
     * @throws std::runtime_error  Failed to get the home directory.
     * @throws std::runtime_error  The function is not yet available on the OS.
     *
     * @return The home directory of the current user.
     */
    static auto getHome() -> Path;

    /**
     * @brief Get the path to a new temporary directory.
     *
     * @param prefix  The prefix for the directory. [`""`]
     *
     * @throws std::runtime_error  Failed to create the temporary directory.
     * @throws std::runtime_error  The function is not yet available on the OS.
     *
     * @return The path to a new temporary directory.
     */
    static auto getTemporaryDirectory(std::string_view prefix = "") -> Path;
};

}

#endif
