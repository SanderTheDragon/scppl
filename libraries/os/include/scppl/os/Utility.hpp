// SPDX-FileCopyrightText: 2021-2022 SanderTheDragon <sanderthedragon@zoho.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef SCPPL_OS_UTILITY_HPP_
#define SCPPL_OS_UTILITY_HPP_

#include <string>
#include <string_view>

namespace scppl {

/**
 * @brief Get the value of an environment variable, or fallback if it is not
 *        defined.
 *
 * @param variable  The variable to get the value for.
 * @param fallback  The value if the variable is not defined. [`""`]
 *
 * @return The value of the variable or the fallback.
 */
auto environment(std::string_view variable, std::string const& fallback = "")
    -> std::string;

/**
 * @brief Set the value of an environment variable.
 *
 * @param variable   The variable to set.
 * @param value      The value to set the variable to.
 * @param overwrite  Overwrite the current value if `true`. [`false`]
 *
 * @return `true` if successful.
 */
auto setEnvironment(std::string_view variable, std::string_view value,
                    bool overwrite = false)
    -> bool;

/**
 * @brief Get the value of a system configuration, or fallback if it is not
 *        defined (fallback is always returned on non-UNIX based systems).
 *
 * @param name      The name of the system configuration to get the value for.
 * @param fallback  The value if the configuration is not defined. [`-1`]
 *
 * @return The value of the system configuration or the fallback.
 */
auto systemConfig(int name, long fallback = -1)
    -> long;

}

#endif
