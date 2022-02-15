// SPDX-FileCopyrightText: 2021-2022 SanderTheDragon <sanderthedragon@zoho.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef SCPPL_BINARY_BINARYSTRING_HPP_
#define SCPPL_BINARY_BINARYSTRING_HPP_

#include <string>
#include <string_view>
#include <vector>

#ifdef SCPPL_CONFIG_BINARY_USE_ICU
#include <unicode/ucnv.h>
#include <unicode/ustring.h>
#endif

#include "scppl/binary/Concepts.hpp"

namespace scppl {

/**
 * @brief Encode strings to and decode strings from binary data.
 *
 * @tparam ByteT       The type to use as a byte. [`char`]
 * @tparam CharT       The type to use as a character. [`char`]
 * @tparam CharTraits  The traits of the character type.
 *                     [`std::char_traits<CharT>`]
 */
template<typename ByteT = char,
         typename CharT = char, typename CharTraits = std::char_traits<CharT>>
class BinaryString
{
public:
    /// The byte type of this `BinaryString` instance.
    using Byte = ByteT;

    /// The character type of this `BinaryString` instance.
    using Char = CharT;

    /// A simple alias for an array of `Byte`s.
    using ByteVector = std::vector<Byte>;

    /// A simple alias for a string of `Char`s with `CharTraits`.
    using String = std::basic_string<Char, CharTraits>;

    /// A simple alias for a string view of `Char`s with `CharTraits`.
    using StringView = std::basic_string_view<Char, CharTraits>;

    /**
     * @brief Encode a string to binary data.
     *
     * @details Encoding is done using ICU if `SCPPL_CONFIG_BINARY_USE_ICU` is
     *          defined, which requires ICU to be found.
     *
     * @warning If ICU is not found or `SCPPL_CONFIG_BINARY_USE_ICU` is
     *          undefined, then the string is copied without encoding it.
     *
     * @param string    The string to encode.
     * @param encoding  The encoding to use. ["UTF-8"]
     *
     * @throws std::runtime_error  An UCI error occurred.
     *
     * @return The encoded string.
     */
    static auto encode(StringView string, std::string_view encoding = "UTF-8")
        -> ByteVector
    {
        ByteVector data{};

#ifdef SCPPL_CONFIG_BINARY_USE_ICU
        UErrorCode error{};

        std::u16string uString = toUString(string);
        auto uStringLength = static_cast<int32_t>(std::ranges::size(uString));

        UConverter* converter = ucnv_open(std::ranges::data(encoding), &error);
        if (U_FAILURE(error))
            throw std::runtime_error(u_errorName(error));

        int32_t dataLength =
            UCNV_GET_MAX_BYTES_FOR_STRING(uStringLength,
                                          ucnv_getMaxCharSize(converter));

        data.resize(dataLength);
        if constexpr(std::is_signed_v<Byte>)
        {
            dataLength =
                ucnv_fromUChars(converter,
                                std::ranges::data(data), dataLength,
                                std::ranges::data(uString), uStringLength,
                                &error);
        }
        else
        {
            std::vector<char> toData(dataLength);
            dataLength =
                ucnv_fromUChars(converter,
                                std::ranges::data(toData), dataLength,
                                std::ranges::data(uString), uStringLength,
                                &error);

            std::ranges::copy_n(std::ranges::begin(toData), dataLength,
                                std::ranges::begin(data));
        }

        ucnv_close(converter);

        if (U_FAILURE(error))
            throw std::runtime_error(u_errorName(error));

        data.resize(dataLength);
#else
        std::ranges::copy(std::ranges::begin(string), std::ranges::end(string),
                          std::back_inserter(data));
#endif

        return data;
    }

    /**
     * @brief Decode a range of `Byte`s into a string.
     *
     * @details Decoding is done using ICU if `SCPPL_CONFIG_BINARY_USE_ICU` is
     *          defined, which requires ICU to be found.
     *
     * @warning If ICU is not found or `SCPPL_CONFIG_BINARY_USE_ICU` is
     *          undefined, then the data is copied without decoding it.
     *
     * @param data      The data to decode.
     * @param encoding  The encoding to use. ["UTF-8"]
     *
     * @throws std::runtime_error  An UCI error occurred.
     *
     * @return The decoded data.
     */
    static auto decode(RangeOfEqualSizedType<Byte> auto data,
                       std::string_view encoding = "UTF-8")
        -> String
    {
        String string{};

#if SCPPL_CONFIG_BINARY_USE_ICU
        UErrorCode error{};

        UConverter* converter = ucnv_open(std::ranges::data(encoding), &error);
        if (U_FAILURE(error))
            throw std::runtime_error(u_errorName(error));

        std::u16string uString{};

        auto dataLength = static_cast<int32_t>(std::ranges::size(data));
        int32_t uStringLength = dataLength;

        uString.resize(uStringLength);
        if constexpr(std::is_signed_v<Byte>)
        {
            uStringLength =
                ucnv_toUChars(converter,
                              std::ranges::data(uString), uStringLength,
                              std::ranges::data(data), dataLength,
                              &error);
        }
        else
        {
            std::vector<char> fromData(std::ranges::begin(data),
                                       std::ranges::end(data));
            uStringLength =
                ucnv_toUChars(converter,
                              std::ranges::data(uString), uStringLength,
                              std::ranges::data(fromData), dataLength,
                              &error);
        }

        ucnv_close(converter);

        if (U_FAILURE(error))
            throw std::runtime_error(u_errorName(error));

        uString.resize(uStringLength);
        string = fromUString(uString);
#else
        std::ranges::copy(std::ranges::begin(data), std::ranges::end(data),
                          std::back_inserter(string));
#endif

        return string;
    }

private:
#ifdef SCPPL_CONFIG_BINARY_USE_ICU
    /**
     * @brief Convert a UTF-8, UTF-16 or UTF-32 string to a UCI string.
     *
     * @param string  The UTF-8, UTF-16 or UTF-32 string to convert.
     *
     * @throws std::runtime_error  An UCI error occurred.
     *
     * @return The UCI string.
     */
    static auto toUString(StringView string)
        -> std::u16string
    {
        std::u16string uString{};

        UErrorCode error{};

        auto stringLength = static_cast<int32_t>(std::ranges::size(string));
        int32_t uStringLength = stringLength;

        uString.resize(uStringLength);

        if constexpr(sizeof(Char) == 1)
        {
            // NOLINTBEGIN: Allow `reinterpret_cast`
            auto const* charString =
                reinterpret_cast<char const*>(std::ranges::data(string));
            // NOLINTEND

            u_strFromUTF8(std::ranges::data(uString), uStringLength,
                          &uStringLength,
                          charString, stringLength,
                          &error);
        }
        else if constexpr(sizeof(Char) == 2)
        {
            std::ranges::copy(std::ranges::begin(string),
                              std::ranges::end(string),
                              std::ranges::begin(uString));
        }
        else if constexpr(sizeof(Char) == 4)
        {
            // NOLINTBEGIN: Allow `reinterpret_cast`
            auto const* uchar32String =
                reinterpret_cast<UChar32 const*>(std::ranges::data(string));
            // NOLINTEND

            u_strFromUTF32(std::ranges::data(uString), uStringLength,
                           &uStringLength,
                           uchar32String, stringLength,
                           &error);
        }

        if (U_FAILURE(error))
            throw std::runtime_error(u_errorName(error));

        uString.resize(uStringLength);

        return uString;
    }

    /**
     * @brief Convert an UCI string to a UTF-8, UTF-16 or UTF-32 string.
     *
     * @param string  The UCI string to convert.
     *
     * @throws std::runtime_error  An UCI error occurred.
     *
     * @return The UTF-8, UTF-16 or UTF-32 string.
     */
    static auto fromUString(std::u16string uString)
        -> String
    {
        String string{};

        UErrorCode error{};

        auto uStringLength = static_cast<int32_t>(std::ranges::size(uString));
        int32_t stringLength = uStringLength;
        if constexpr(sizeof(Char) == 1)
            stringLength *= 4;

        string.resize(stringLength);

        if constexpr(sizeof(Char) == 1)
        {
            // NOLINTBEGIN: Allow `reinterpret_cast`
            auto* charString =
                reinterpret_cast<char*>(std::ranges::data(string));
            // NOLINTEND

            u_strToUTF8(charString, stringLength, &stringLength,
                        std::ranges::data(uString), uStringLength,
                        &error);
        }
        else if constexpr(sizeof(Char) == 2)
        {
            std::ranges::copy(std::ranges::begin(uString),
                              std::ranges::end(uString),
                              std::ranges::begin(string));
        }
        else if constexpr(sizeof(Char) == 4)
        {
            // NOLINTBEGIN: Allow `reinterpret_cast`
            auto* uchar32String =
                reinterpret_cast<UChar32*>(std::ranges::data(string));
            // NOLINTEND

            u_strToUTF32(uchar32String, stringLength, &stringLength,
                         std::ranges::data(uString), uStringLength,
                         &error);
        }

        if (U_FAILURE(error))
            throw std::runtime_error(u_errorName(error));

        string.resize(stringLength);

        return string;
    }
#endif
};

}

#endif
