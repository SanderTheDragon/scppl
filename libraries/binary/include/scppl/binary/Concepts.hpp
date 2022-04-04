// SPDX-FileCopyrightText: 2021-2022 SanderTheDragon <sanderthedragon@zoho.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef SCPPL_BINARY_CONCEPTS_HPP_
#define SCPPL_BINARY_CONCEPTS_HPP_

#include <ranges>

#include "scppl/binary/Traits.hpp"

namespace scppl {

/**
 * @brief `Range` must be a range of a type convertible to `T`.
 *
 * @tparam Range   The range to test.
 * @tparam T       The type the range should be.
 * @tparam RangeT  The range value type, should probably not be defined.
 */
template<typename Range,
         typename T, typename RangeT = std::ranges::range_value_t<Range>>
concept RangeOf = std::ranges::range<Range>
                  && std::convertible_to<RangeT, T>;

/**
 * @brief `Range` must be a range of a equal sized type convertible to `T`.
 *
 * @sa @ref scppl::RangeOf
 *
 * @tparam Range   The range to test.
 * @tparam T       The type the range should be.
 * @tparam RangeT  The range value type, should probably not be defined.
 */
template<typename Range,
         typename T, typename RangeT = std::ranges::range_value_t<Range>>
concept RangeOfEqualSizedType = RangeOf<Range, T>
                                && (sizeof(RangeT) == sizeof(T));

/**
 * @brief Concept for a packable type.
 *
 * @sa @ref scppl::PackableTrait
 */
template<typename T>
concept Packable = PackableTrait<T>::value;

/**
 * @brief Concept for an unpackable type.
 *
 * @sa @ref scppl::UnpackableTrait
 */
template<typename T>
concept Unpackable = UnpackableTrait<T>::value;

/**
 * @brief Concept for an input stream type.
 *
 * @details A type is an input stream if it has a read function accepting a
 *          pointer to it's underlying data type and a length.
 */
template<template<typename, typename...> typename StreamT,
         typename ByteT, typename... Ts>
concept InputStream = requires(StreamT<ByteT, Ts...> stream, ByteT* data)
{
    stream.read(data, std::declval<std::size_t>());
};

/**
 * @brief Concept for an output stream type.
 *
 * @details A type is an output stream if it has a write function accepting a
 *          pointer to it's underlying data type and a length.
 */
template<template<typename, typename...> typename StreamT,
         typename ByteT, typename... Ts>
concept OutputStream = requires(StreamT<ByteT, Ts...> stream, ByteT* data)
{
    stream.write(data, std::declval<std::size_t>());
};

}

#endif
