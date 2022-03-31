// SPDX-FileCopyrightText: 2021-2022 SanderTheDragon <sanderthedragon@zoho.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "scppl/os/String.hpp"

#include "scppl/os/Utility.hpp"

namespace scppl {

auto String::expand(std::string_view string)
    -> std::string
{
#ifdef SCPPL_OS_UNIX
    std::string result{string};
    std::smatch match{};
    while (std::regex_search(result, match, EnvironmentVariableRegex))
    {
        result = result.replace(match.position(0), match.length(0),
                                environment(match.str(1)));
    }

    return result;
#else
    throw std::runtime_error(SCPPL_OS_NAME " is not supported (yet)");
#endif
}

}
