// SPDX-FileCopyrightText: 2021-2022 SanderTheDragon <sanderthedragon@zoho.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "scppl/os/Utility.hpp"

#include "scppl/os/Platform.hpp"

#ifdef SCPPL_OS_UNIX
#include <unistd.h>
#endif

#include <cstdlib>

namespace scppl {

auto environment(std::string_view variable, std::string const& fallback)
    -> std::string
{
    if (char* value = std::getenv(variable.data()); value != nullptr)
        return value;

    return fallback;
}

auto setEnvironment(std::string_view variable, std::string_view value,
                    bool overwrite)
    -> bool
{
    return (::setenv(variable.data(), value.data(), overwrite) == 0);
}

auto systemConfig(int name, long fallback)
    -> long
{
#ifdef SCPPL_OS_UNIX
    if (long value = ::sysconf(name); value != -1)
        return value;
#endif

    return fallback;
}

}
