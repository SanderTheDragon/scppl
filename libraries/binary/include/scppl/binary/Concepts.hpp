// SPDX-FileCopyrightText: 2021 SanderTheDragon <sanderthedragon@zoho.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef SCPPL_BINARY_CONCEPTS_HPP_
#define SCPPL_BINARY_CONCEPTS_HPP_

#include <ranges>

namespace scppl {

/**
 * @brief `Range` must be a range of a same sized type convertible to `T`.
 *
 * @tparam Range   The range to test.
 * @tparam T       The type the range should be.
 * @tparam RangeT  The range type, should probably not be defined.
 */
template<typename Range,
         typename T, typename RangeT = std::ranges::range_value_t<Range>>
concept RangeOf = std::ranges::range<Range>
                  && std::convertible_to<RangeT, T>
                  && (sizeof(RangeT) == sizeof(T));

/**
 * @brief `T` must be an object type and not a range.
 *
 * @tparam T  The type to test.
 */
template<typename T>
concept Packable = std::is_object_v<T> && !std::ranges::range<T>;

/**
 * @brief `T` must be an object type and not a range.
 *
 * @tparam T  The type to test.
 */
template<typename T>
concept Unpackable = std::is_object_v<T> && !std::ranges::range<T>;

}

#endif
