// SPDX-FileCopyrightText: 2021-2022 SanderTheDragon <sanderthedragon@zoho.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef SCPPL_OS_STANDARDPATHS_HPP_
#define SCPPL_OS_STANDARDPATHS_HPP_

#include "scppl/os/Platform.hpp"

#include <filesystem>
#include <string_view>
#include <vector>

#ifdef SCPPL_OS_LINUX
#include <functional>
#include <string>
#include <utility>
#include <variant>
#endif

#if SCPPL_CONFIG_OS_CACHE_XDG_USERDIRS
#include <map>
#endif

namespace scppl {

class StandardPaths
{
public:
    /// A simple alias for a `std::filesystem::path`.
    using Path = std::filesystem::path;

    /// The possible directories that can be retrieved.
    enum DirectoryType
    {
        // XDG Base Directories
        // Multiple
        ConfigDirectory,
        DataDirectory,
        // Single
        CacheDirectory,
        StateDirectory,
        RuntimeDirectory,

        // XDG User Directories
        DesktopDirectory,
        DocumentsDirectory,
        DownloadDirectory,
        MusicDirectory,
        PicturesDirectory,
        PublicShareDirecotry,
        TemplatesDirectory,
        VideosDirectory
    };

    /**
     * @{
     *
     * @name get...Director(y|ies)
     *
     * @details The following directories are found in the following ways.
     *
     * <table>
     *   <tr>
     *     <th>Directory</th>
     *     <th>Linux</th>
     *   </tr>
     *   <tr>
     *     <td>Config</td>
     *     <td>
     *       All of the following:
     *       <ul>
     *         <li>`$XDG_CONFIG_HOME` or `"$HOME/.config"`</li>
     *         <li>`$XDG_CONFIG_DIRS` or `"/etc/xdg"`</li>
     *       </ul>
     *     </td>
     *   </tr>
     *   <tr>
     *     <td>Data</td>
     *     <td>
     *       All of the following:
     *       <ul>
     *         <li>`$XDG_DATA_HOME` or `"$HOME/.local/share"`</li>
     *         <li>`$XDG_DATA_DIRS` or `"/usr/local/share"`, `"/usr/share"`</li>
     *       </ul>
     *     </td>
     *   </tr>
     *   <tr>
     *     <td>Cache</td>
     *     <td>
     *       <ul>
     *         <li>`$XDG_CACHE_HOME` or `"$HOME/.cache"`</li>
     *       </ul>
     *     </td>
     *   </tr>
     *   <tr>
     *     <td>State</td>
     *     <td>
     *       <ul>
     *         <li>`$XDG_STATE_HOME` or `"$HOME/.local/state"`</li>
     *       </ul>
     *     </td>
     *   </tr>
     *   <tr>
     *     <td>Runtime</td>
     *     <td>
     *       <ul>
     *         <li>`$XDG_RUNTIME_DIR` or a new temporary directory</li>
     *       </ul>
     *
     *       If `SCPPL_CONFIG_OS_CACHE_XDG_RUNTIME_DIR_FALLBACK` is enabled,
     *       then the temporary directory stays the same between calls.
     *     </td>
     *   </tr>
     *   <tr>
     *     <td>Desktop</td>
     *     <td>
     *       The first of the following:
     *       <ul>
     *         <li>`XDG_DESKTOP_DIR` from `"user-dirs.dirs"`</li>
     *         <li>`DESKTOP` from `"user-dirs.defaults"`</li>
     *       </ul>
     *     </td>
     *   </tr>
     *   <tr>
     *     <td>Documents</td>
     *     <td>
     *       The first of the following:
     *       <ul>
     *         <li>`XDG_DOCUMENTS_DIR` from `"user-dirs.dirs"`</li>
     *         <li>`DOCUMENTS` from `"user-dirs.defaults"`</li>
     *       </ul>
     *     </td>
     *   </tr>
     *   <tr>
     *     <td>Download</td>
     *     <td>
     *       The first of the following:
     *       <ul>
     *         <li>`XDG_DOWNLOAD_DIR` from `"user-dirs.dirs"`</li>
     *         <li>`DOWNLOAD` from `"user-dirs.defaults"`</li>
     *       </ul>
     *     </td>
     *   </tr>
     *   <tr>
     *     <td>Music</td>
     *     <td>
     *       The first of the following:
     *       <ul>
     *         <li>`XDG_MUSIC_DIR` from `"user-dirs.dirs"`</li>
     *         <li>`MUSIC` from `"user-dirs.defaults"`</li>
     *       </ul>
     *     </td>
     *   </tr>
     *   <tr>
     *     <td>Pictures</td>
     *     <td>
     *       The first of the following:
     *       <ul>
     *         <li>`XDG_PICTURES_DIR` from `"user-dirs.dirs"`</li>
     *         <li>`PICTURES` from `"user-dirs.defaults"`</li>
     *       </ul>
     *     </td>
     *   </tr>
     *   <tr>
     *     <td>PublicShare</td>
     *     <td>
     *       The first of the following:
     *       <ul>
     *         <li>`XDG_PUBLICSHARE_DIR` from `"user-dirs.dirs"`</li>
     *         <li>`PUBLICSHARE` from `"user-dirs.defaults"`</li>
     *       </ul>
     *     </td>
     *   </tr>
     *   <tr>
     *     <td>Templates</td>
     *     <td>
     *       The first of the following:
     *       <ul>
     *         <li>`XDG_TEMPLATES_DIR` from `"user-dirs.dirs"`</li>
     *         <li>`TEMPLATES` from `"user-dirs.defaults"`</li>
     *       </ul>
     *     </td>
     *   </tr>
     *   <tr>
     *     <td>Videos</td>
     *     <td>
     *       The first of the following:
     *       <ul>
     *         <li>`XDG_VIDEOS_DIR` from `"user-dirs.dirs"`</li>
     *         <li>`VIDEOS` from `"user-dirs.defaults"`</li>
     *       </ul>
     *     </td>
     *   </tr>
     * </table>
     */

    static auto getConfigDirectories() -> std::vector<Path>;
    static auto getDataDirectories() -> std::vector<Path>;

    static auto getCacheDirectory() -> Path;
    static auto getStateDirectory() -> Path;
    static auto getRuntimeDirectory() -> Path;

    static auto getDesktopDirectory() -> Path;
    static auto getDocumentsDirectory() -> Path;
    static auto getDownloadDirectory() -> Path;
    static auto getMusicDirectory() -> Path;
    static auto getPicturesDirectory() -> Path;
    static auto getPublicShareDirectory() -> Path;
    static auto getTemplatesDirectory() -> Path;
    static auto getVideosDirectory() -> Path;

    /** @} */

    /**
     * @brief Get a vector of directories for its type.
     *
     * @details This calls the loose functions and returns their result
     *          converted to a vector (if needed). Like
     *          `getConfigDirectories();` for `ConfigDirectory` or
     *          `{ getCacheDirectory() };` for `CacheDirectory`.
     *
     * @param type  The type of directories to get.
     *
     * @return The vector of directories.
     */
    static auto getDirectories(DirectoryType type) -> std::vector<Path>;

    /**
     * @brief Find a file in any of the directories for a directory type.
     *
     * @param type  The type of directory to find the file in.
     * @param file  The relative path to a file to find.
     *
     * @return The path to the file, or `{}` if it does not exist.
     */
    static auto findFile(DirectoryType type, std::string_view file) -> Path;

private:
#ifdef SCPPL_OS_LINUX
    /// A vector of pairs
    /// The first item of the pair is the XDG variable
    /// The second item is either the default path(s), or a function to generate
    /// the path(s)
    using XDGMap = std::vector<std::pair<std::string_view,
                                         std::variant<std::string,
                                                      std::function<Path()>>>>;

    /// Callback for `readXDGUserDirsFile`
    /// Arguments are name and path
    /// Return false to stop iterating
    using UserDirsCallback = std::function<bool(std::string_view, Path)>;

#if SCPPL_CONFIG_OS_CACHE_XDG_USERDIRS
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
    static inline std::map<std::string, Path, std::less<>> UserDirs{};
#endif

#if SCPPL_CONFIG_OS_CACHE_XDG_RUNTIME_DIR_FALLBACK
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
    static inline Path RuntimeDirectoryFallback{};
#endif

    /**
     * @brief Get XDG directories from enviroment variables.
     *
     * @param items  A list of pairs of a XDG variable and fallback.
     *
     * @return The paths.
     */
    static auto getXDGDirectories(XDGMap const& items) -> std::vector<Path>;

    /**
     * @brief Get XDG directories from "user-dirs.defaults" and
     *        "user-dirs.dirs".
     *
     * @param name  The name of the XDG directory to get.
     *
     * @return The path.
     */
    static auto getXDGUserDirectory(std::string_view name) -> Path;

    /**
     * @brief Read "user-dirs.defaults" or "user-dirs.dirs".
     *
     * @param path      The path to the file to read.
     * @param callback  The function to call with the name and path as
     *                  arguments.
     */
    static void readXDGUserDirsFile(Path const& path,
                                    UserDirsCallback const& callback);
#endif
};

}

#endif
