// SPDX-FileCopyrightText: 2021-2022 SanderTheDragon <sanderthedragon@zoho.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef SCPPL_OS_STRING_HPP_
#define SCPPL_OS_STRING_HPP_

#include "scppl/os/Platform.hpp"

#include <cstring>
#include <string>
#include <string_view>
#include <vector>

#ifdef SCPPL_OS_UNIX
#include <regex>
#endif

namespace scppl {

class String
{
public:
    /**
     * @brief Split a string by a delimiter (the delimiter can be any type
     *        accepted by `std::string_view::find_first_of`).
     *
     * @param string     The string to split.
     * @param delimiter  The delimiter to split the string by.
     *
     * @return The parts of the string.
     */
    template<typename T>
    requires requires(std::string_view s, T d) { s.find_first_of(d); }
    static auto split(std::string_view string, T delimiter)
        -> std::vector<std::string>
    {
        std::size_t length = 1;
        if constexpr(std::is_same_v<T, std::string_view>)
            length = delimiter.length();
        else if constexpr(std::is_same_v<T, char const*>)
            length = std::strlen(delimiter);

        std::vector<std::string> parts{};
        std::size_t position = 0;
        for (std::size_t next = string.find_first_of(delimiter, position);
             next != std::string::npos;
             position = next + length,
             next = string.find_first_of(delimiter, position))
        {
            parts.emplace_back(string.substr(position, next - position));
        }

        // Add the last part
        parts.emplace_back(string.substr(position));

        return parts;
    }

    /**
     * @brief Expand the environment variables in a string.
     *
     * @details  On UNIX based systems, this replaces everything in the form of
     *           "$VARIABLE" and "${VARIABLE}" (also "${VARIABLE" and
     *           "$VARIABLE}" because regex). An undefined variable is replaced
     *           with "".
     *
     * @param string  The string to expand.
     *
     * @throws std::runtime_error  The function is not yet available on the OS.
     *
     * @return The expanded string.
     */
    static auto expand(std::string_view string) -> std::string;

private:
#ifdef SCPPL_OS_UNIX
    inline static std::regex const EnvironmentVariableRegex{
        R"(\$\{?([A-Za-z_][A-Za-z0-9_]+)\}?)"};
#endif
};

}

#endif
