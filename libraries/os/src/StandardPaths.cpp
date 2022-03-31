// SPDX-FileCopyrightText: 2021-2022 SanderTheDragon <sanderthedragon@zoho.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "scppl/os/StandardPaths.hpp"

// IWYU suggests <ext/alloc_traits.h>, but extensions should not be used
// IWYU pragma: no_include <ext/alloc_traits.h>

#ifdef SCPPL_OS_LINUX
#include <fstream>
#include <memory>
#else
#include <stdexcept>
#endif

#include "scppl/os/FileSystem.hpp"
#include "scppl/os/String.hpp"
#include "scppl/os/Utility.hpp"

namespace scppl {

auto StandardPaths::getConfigDirectories()
    -> std::vector<Path>
{
#ifdef SCPPL_OS_LINUX
    return getXDGDirectories({
        { "XDG_CONFIG_HOME", FileSystem::getHome() / ".config" },
        { "XDG_CONFIG_DIRS", "/etc/xdg" }
    });
#else
    throw std::runtime_error(SCPPL_OS_NAME " is not supported (yet)");
#endif
}

auto StandardPaths::getDataDirectories()
    -> std::vector<Path>
{
#ifdef SCPPL_OS_LINUX
    return getXDGDirectories({
        { "XDG_DATA_HOME", FileSystem::getHome() / ".local/share" },
        { "XDG_DATA_DIRS", "/usr/local/share:/usr/share" }
    });
#else
    throw std::runtime_error(SCPPL_OS_NAME " is not supported (yet)");
#endif
}

auto StandardPaths::getCacheDirectory()
    -> Path
{
#ifdef SCPPL_OS_LINUX
    return getXDGDirectories({
        { "XDG_CACHE_HOME", FileSystem::getHome() / ".cache" }
    }).at(0);
#else
    throw std::runtime_error(SCPPL_OS_NAME " is not supported (yet)");
#endif
}

auto StandardPaths::getStateDirectory()
    -> Path
{
#ifdef SCPPL_OS_LINUX
    return getXDGDirectories({
        { "XDG_STATE_HOME", FileSystem::getHome() / ".local/state" }
    }).at(0);
#else
    throw std::runtime_error(SCPPL_OS_NAME " is not supported (yet)");
#endif
}

auto StandardPaths::getRuntimeDirectory()
    -> Path
{
#ifdef SCPPL_OS_LINUX
    return getXDGDirectories({
        {
            "XDG_RUNTIME_DIR",
            []() -> Path
            {
#if SCPPL_CONFIG_OS_CACHE_XDG_RUNTIME_DIR_FALLBACK
                if (RuntimeDirectoryFallback.empty())
                {
                    RuntimeDirectoryFallback =
                        FileSystem::getTemporaryDirectory("run");
                }

                return RuntimeDirectoryFallback;
#else
                return FileSystem::getTemporaryDirectory("run");
#endif
            }
        }
    }).at(0);
#else
    throw std::runtime_error(SCPPL_OS_NAME " is not supported (yet)");
#endif
}

// NOLINTNEXTLINE(misc-no-recursion)
auto StandardPaths::getDesktopDirectory()
    -> Path
{
#ifdef SCPPL_OS_LINUX
    return getXDGUserDirectory("DESKTOP");
#else
    throw std::runtime_error(SCPPL_OS_NAME " is not supported (yet)");
#endif
}

// NOLINTNEXTLINE(misc-no-recursion)
auto StandardPaths::getDocumentsDirectory()
    -> Path
{
#ifdef SCPPL_OS_LINUX
    return getXDGUserDirectory("DOCUMENTS");
#else
    throw std::runtime_error(SCPPL_OS_NAME " is not supported (yet)");
#endif
}

// NOLINTNEXTLINE(misc-no-recursion)
auto StandardPaths::getDownloadDirectory()
    -> Path
{
#ifdef SCPPL_OS_LINUX
    return getXDGUserDirectory("DOWNLOAD");
#else
    throw std::runtime_error(SCPPL_OS_NAME " is not supported (yet)");
#endif
}

// NOLINTNEXTLINE(misc-no-recursion)
auto StandardPaths::getMusicDirectory()
    -> Path
{
#ifdef SCPPL_OS_LINUX
    return getXDGUserDirectory("MUSIC");
#else
    throw std::runtime_error(SCPPL_OS_NAME " is not supported (yet)");
#endif
}

// NOLINTNEXTLINE(misc-no-recursion)
auto StandardPaths::getPicturesDirectory()
    -> Path
{
#ifdef SCPPL_OS_LINUX
    return getXDGUserDirectory("PICTURES");
#else
    throw std::runtime_error(SCPPL_OS_NAME " is not supported (yet)");
#endif
}

// NOLINTNEXTLINE(misc-no-recursion)
auto StandardPaths::getPublicShareDirectory()
    -> Path
{
#ifdef SCPPL_OS_LINUX
    return getXDGUserDirectory("PUBLICSHARE");
#else
    throw std::runtime_error(SCPPL_OS_NAME " is not supported (yet)");
#endif
}

// NOLINTNEXTLINE(misc-no-recursion)
auto StandardPaths::getTemplatesDirectory()
    -> Path
{
#ifdef SCPPL_OS_LINUX
    return getXDGUserDirectory("TEMPLATES");
#else
    throw std::runtime_error(SCPPL_OS_NAME " is not supported (yet)");
#endif
}

// NOLINTNEXTLINE(misc-no-recursion)
auto StandardPaths::getVideosDirectory()
    -> Path
{
#ifdef SCPPL_OS_LINUX
    return getXDGUserDirectory("VIDEOS");
#else
    throw std::runtime_error(SCPPL_OS_NAME " is not supported (yet)");
#endif
}

// NOLINTNEXTLINE(misc-no-recursion)
auto StandardPaths::getDirectories(DirectoryType type)
    -> std::vector<Path>
{
    switch (type)
    {
    case ConfigDirectory:      return getConfigDirectories();
    case DataDirectory:        return getDataDirectories();

    case CacheDirectory:       return { getCacheDirectory() };
    case RuntimeDirectory:     return { getRuntimeDirectory() };
    case StateDirectory:       return { getStateDirectory() };

    case DesktopDirectory:     return { getDesktopDirectory() };
    case DocumentsDirectory:   return { getDocumentsDirectory() };
    case DownloadDirectory:    return { getDownloadDirectory() };
    case MusicDirectory:       return { getMusicDirectory() };
    case PicturesDirectory:    return { getPicturesDirectory() };
    case PublicShareDirecotry: return { getPublicShareDirectory() };
    case TemplatesDirectory:   return { getTemplatesDirectory() };
    case VideosDirectory:      return { getVideosDirectory() };
    }

    return {}; // GCOVR_EXCL_LINE, should not be reached
}

// NOLINTNEXTLINE(misc-no-recursion)
auto StandardPaths::findFile(DirectoryType type, std::string_view file)
    -> Path
{
    for (auto const& directory : getDirectories(type))
    {
        auto path = directory / file;
        if (std::filesystem::exists(path) &&
            !std::filesystem::is_directory(path))
        {
            return path;
        }
    }

    return {}; // GCOVR_EXCL_LINE, should not be reached
}

#ifdef SCPPL_OS_LINUX
auto StandardPaths::getXDGDirectories(XDGMap const& items)
    -> std::vector<Path>
{
    std::vector<Path> paths{};

    for (auto const& pair : items)
    {
        std::string path{};
        if (std::holds_alternative<std::string>(pair.second))
            path = environment(pair.first, std::get<std::string>(pair.second));
        else
        {
            path = environment(pair.first);
            if (path.empty())
                path = std::get<std::function<Path()>>(pair.second)();
        }

        for (auto const& part : String::split(path, ":"))
            paths.emplace_back(part);
    }

    return paths;
}

// `getXDGUserDirectory` calls `findFile`, which calls `getDirectories`, which
// may call any of the `get.*Director(y|ies)`, from which some call
// `getXDGUserDirectory`.
// This causes the warning about recursion, but since `getXDGUserDirectory`
// only calls `findFile` with `ConfigDirectory`, which does not call
// `getXDGUserDirectory`, so no actual recursion happens.
// NOLINTNEXTLINE(misc-no-recursion)
auto StandardPaths::getXDGUserDirectory(std::string_view name)
    -> Path
{
    // Small function to convert "XDG_<NAME>_DIR" to "<NAME>"
    auto nameFromKey = [](std::string_view key) -> std::string_view
    {
        auto start = key.find_first_of('_') + 1;
        auto length = key.find_last_of('_') - start;
        return key.substr(start, length);
    };

    // "user-dirs.dirs" often uses `$HOME`, so make sure it is set
    setEnvironment("HOME", FileSystem::getHome().string());

#if SCPPL_CONFIG_OS_CACHE_XDG_USERDIRS
    if (!UserDirs.empty() && UserDirs.contains(name))
        return UserDirs.at(std::string{name});

    readXDGUserDirsFile(findFile(ConfigDirectory, "user-dirs.defaults"),
                        [](std::string_view key, Path path) -> bool
    {
        UserDirs[std::string{key}] = std::move(path);
        return true;
    });

    readXDGUserDirsFile(findFile(ConfigDirectory, "user-dirs.dirs"),
                                 [&](std::string_view key, Path path) -> bool
    {
        UserDirs[std::string{nameFromKey(key)}] = std::move(path);
        return true;
    });

    if (!UserDirs.empty() && UserDirs.contains(name))
        return UserDirs.at(std::string{name});

    return {}; // GCOVR_EXCL_LINE, should not be reached
#else
    Path result{};

    readXDGUserDirsFile(findFile(ConfigDirectory, "user-dirs.dirs"),
                        [&](std::string_view key, Path path) -> bool
    {
        if (nameFromKey(key) == name)
        {
            result = std::move(path);
            return false;
        }

        return true;
    });

    if (std::filesystem::is_directory(result))
        return result;

    readXDGUserDirsFile(findFile(ConfigDirectory, "user-dirs.defaults"),
                        [&](std::string_view key, Path path) -> bool
    {
        if (key == name)
        {
            result = std::move(path);
            return false;
        }

        return true;
    });

    if (std::filesystem::is_directory(result))
        return result;

    return {}; // GCOVR_EXCL_LINE, should not be reached
#endif
}

void StandardPaths::readXDGUserDirsFile(Path const& path,
                                        UserDirsCallback const& callback)
{
    std::ifstream stream(path);

    std::string line{};
    while(std::getline(stream, line))
    {
        auto parts = String::split(line, "=");
        if (parts.size() < 2)
            continue;

        // Remove the '"' from the begin and end
        auto value = parts.at(1);
        if (value.at(0) == '"')
            value = value.substr(1, parts.at(1).length() - 2);

        Path path = String::expand(value);
        if (path.is_relative())
            path = FileSystem::getHome() / path;

        if (!callback(parts.at(0), path))
            break; // GCOVR_EXCL_LINE, is not reached with default options
    }
};

#endif

}
