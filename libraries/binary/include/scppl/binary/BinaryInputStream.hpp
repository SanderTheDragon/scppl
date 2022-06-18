// SPDX-FileCopyrightText: 2021-2022 SanderTheDragon <sanderthedragon@zoho.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef SCPPL_BINARY_BINARYINPUTSTREAM_HPP_
#define SCPPL_BINARY_BINARYINPUTSTREAM_HPP_

#include <bit>
#include <iostream>
#include <ostream>
#include <tuple>
#include <type_traits>

#include "scppl/binary/Binary.hpp"
#include "scppl/binary/BinaryString.hpp"
#include "scppl/binary/Concepts.hpp"
#include "scppl/binary/Utility.hpp"

namespace scppl {

/**
 * @brief Pack unpack data from a stream.
 *
 * @tparam tEndian   The endian of the data. [`std::endian::native`]
 * @tparam StreamT   A type of the stream, must be template class with at least
 *                   one parameter for the type. [`std::basic_istream`]
 * @tparam ByteT     The byte type, should be the same as the first type of
 *                   `StreamT`. [`char`]
 * @tparam StreamTs  Any other type parameters for `StreamT`.
 */
template<std::endian tEndian = std::endian::native,
         template<typename, typename...> typename StreamT = std::basic_istream,
         typename ByteT = char, typename... StreamTs>
requires(InputStream<StreamT, ByteT, StreamTs...>)
class BinaryInputStream
{
public:
    /// The stream type of this `BinaryInputStream` instance.
    using Stream = StreamT<ByteT, StreamTs...>;

    /// The byte type of this `BinaryInputStream` instance.
    using Byte = ByteT;

    /// The `Binary` instance of this `BinaryInputStream` instance.
    using BinaryT = Binary<tEndian, Byte>;

    /// The `BinaryString` instance of this `BinaryOutputStream` instance.
    template<typename CharT, typename CharTraits = std::char_traits<CharT>>
    using BinaryStringT = BinaryString<Byte, CharT, CharTraits>;

    /// The endian of this `BinaryOutputStream` instance.
    static constexpr auto endian() -> std::endian { return tEndian; }

    /**
     * @brief The `BinaryInputStream` constructor.
     *
     * @param stream  A reference to a stream type, like `std::stringstream` or
     *                `std::fstream`.
     */
    BinaryInputStream(Stream& stream) :
        mStream(stream)
    {
        //
    }

    /// Default copy constructor.
    BinaryInputStream(BinaryInputStream const&) = default;

    /// Default move constructor.
    BinaryInputStream(BinaryInputStream&&) noexcept = default;

    /// Default destructor.
    virtual ~BinaryInputStream() noexcept = default;

    /// Default copy assignment operator.
    auto operator=(BinaryInputStream const&) -> BinaryInputStream& = default;

    /// Default move assignment operator.
    auto operator=(BinaryInputStream&&) noexcept
        -> BinaryInputStream& = default;

    /// Read types from a stream
    template<typename T>
    auto operator>>(T& variable)
        -> BinaryInputStream&
    {
        variable = readSingle<T>();

        return *this;
    }

    /**
     * @brief Get the read position of this stream.
     *
     * @return The current read position.
     */
    auto tellInput()
        -> std::size_t
    {
        return mStream.tellg();
    }

    /**
     * @brief Whether the stream is at the end.
     *
     * @return `true` if the stream is at the end.
     */
    auto eofInput()
        -> bool
    {
        return mStream.eof();
    }

    /**
     * @brief Move the read position of this stream.
     *
     * @param offset     The amount of bytes to seek from `direction`. [`0`]
     * @param direction  The direction to search from. [`std::ios::beg`]
     */
    void seekInput(std::size_t offset = 0,
                   std::ios::seekdir direction = std::ios::beg)
    {
        mStream.seekg(offset, direction);
    }

    /**
     * @brief Move the read position of this stream from the begin.
     *
     * @param offset  The amount of bytes to seek from the begin. [`0`]
     */
    void toBeginInput(std::size_t offset = 0)
    {
        seekInput(offset, std::ios::beg);
    }

    /**
     * @brief Move the read position of this stream from the end.
     *
     * @param offset  The amount of bytes to seek from the end. [`0`]
     */
    void toEndInput(std::size_t offset = 0)
    {
        seekInput(offset, std::ios::end);
    }

    /**
     * @brief Move the read position of this stream from the current position.
     *
     * @param offset  The amount of bytes to seek from the current position.
     *                [`0`]
     */
    void skipInput(std::size_t offset = 0)
    {
        seekInput(offset, std::ios::cur);
    }

    /**
     * @brief Read an amount of bytes from the stream into a `std::vector`.
     *
     * @note This requires the stream to be an @ref scppl::InputStream.
     *
     * @param length  The amount of bytes to read.
     *
     * @return A `std::array` of `N` `Byte`s.
     */
    auto readRaw(std::size_t length)
        -> std::vector<Byte>
    {
        std::vector<Byte> data(length);
        mStream.read(std::ranges::data(data), length);

        return data;
    }

    /**
     * @brief Read types from a stream.
     *
     * @note This requires the stream to be an @ref scppl::InputStream.
     *
     * @sa scppl::Binary::unpack()
     *
     * @tparam Ts  The types to read from the stream, must be `Unpackable`.
     *
     * @return A tuple of the read types.
     */
    template<Unpackable... Ts>
    auto read()
        -> std::tuple<Ts...>
    {
        return BinaryT::template unpack<Ts...>(readRaw(lengthOf<Ts...>()));
    }

    /**
     * @brief Read a single type from a stream.
     *
     * @note This requires the stream to be an @ref scppl::InputStream.
     *
     * @sa scppl::Binary::fromBytes()
     *
     * @tparam T  The type to read from the stream, must be `Unpackable`.
     *
     * @return The read value.
     */
    template<Unpackable T>
    auto readSingle()
        -> T
    {
        return BinaryT::template fromBytes<T>(readRaw(lengthOf<T>()));
    }

    /**
     * @brief Read and decode a string from the stream.
     *
     * @tparam CharT       The type to use as character.
     * @tparam CharTraits  The character traits of the character type.
     *
     * @param length    The length of the string to read.
     * @param encoding  The encoding of the string. [`"UTF-8"`]
     *
     * @return The decoded string.
     */
    template<typename CharT = char,
             typename CharTraits = std::char_traits<CharT>>
    auto readString(std::size_t length, std::string_view encoding = "UTF-8")
        -> std::basic_string<CharT>
    {
        return BinaryStringT<CharT, CharTraits>::decode(readRaw(length),
                                                        encoding);
    }

private:
    Stream& mStream{};
};

}

#endif
