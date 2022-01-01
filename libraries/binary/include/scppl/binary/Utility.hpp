// SPDX-FileCopyrightText: 2021 SanderTheDragon <sanderthedragon@zoho.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef SCPPL_BINARY_UTILITY_HPP_
#define SCPPL_BINARY_UTILITY_HPP_

#include <cstdint>

namespace scppl {

/**
 * @brief Calculates the total length of parameter pack `Ts`.
 *
 * @details Calculating is done by calculating the sum of each `sizeof(T)` for
 *          `T` in `Ts...` using a fold expression.
 *
 * @tparam Ts  The types to get the length of.
 *
 * @return The total length of the parameter pack.
 */
template<typename... Ts>
constexpr auto lengthOf()
    -> std::size_t
{
    return (sizeof(Ts) + ...);
}

}

#endif
