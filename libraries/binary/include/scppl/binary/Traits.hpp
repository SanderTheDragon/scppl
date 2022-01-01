// SPDX-FileCopyrightText: 2021 SanderTheDragon <sanderthedragon@zoho.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef SCPPL_BINARY_TRAITS_HPP_
#define SCPPL_BINARY_TRAITS_HPP_

#include <ranges>

namespace scppl {

/**
 * @defgroup scpplPackableTrait scppl::PackableTrait
 *
 * @brief Trait for a packable type.
 *
 * @details A type is packable if it is:
 *          - An object type (excluding ranges).
 *          - A sized range containing a packable type.
 *
 * @sa @ref scppl::Packable
 *
 * @{
 */

template<typename T>
struct PackableTrait : std::false_type {};

template<typename T>
requires(std::is_object_v<T> && !std::ranges::range<T>)
struct PackableTrait<T> : std::true_type {};

template<typename T>
requires(std::ranges::sized_range<T>)
struct PackableTrait<T> : PackableTrait<std::ranges::range_value_t<T>> {};

/** @} */

/**
 * @defgroup scpplUnpackableTrait scppl::UnpackableTrait
 *
 * @brief Trait for an unpackable type.
 *
 * @details A type is unpackable if it is:
 *          - A non-const object type (excluding ranges).
 *          - A non-const sized range containing an unpackable type.
 *
 * @sa @ref scppl::Unpackable
 *
 * @{
 */

template<typename T>
struct UnpackableTrait : std::false_type {};

template<typename T>
requires(std::is_object_v<T> && !std::is_const_v<T> && !std::ranges::range<T>)
struct UnpackableTrait<T> : std::true_type {};

template<typename T>
requires(std::ranges::sized_range<T> && !std::is_const_v<T>)
struct UnpackableTrait<T> : UnpackableTrait<std::ranges::range_value_t<T>> {};

/** @} */

}

#endif
