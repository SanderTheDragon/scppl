// SPDX-FileCopyrightText: 2021-2022 SanderTheDragon <sanderthedragon@zoho.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef SCPPL_BINARY_BINARYSTREAM_HPP_
#define SCPPL_BINARY_BINARYSTREAM_HPP_

#include <bit>
#include <iostream>

#include "scppl/binary/Binary.hpp"
#include "scppl/binary/BinaryString.hpp"
#include "scppl/binary/Concepts.hpp"
#include "scppl/binary/Utility.hpp"

namespace scppl {

/**
 * @brief Pack data into and unpack data from a stream.
 *
 * @tparam tEndian   The endian of the data. [`std::endian::native`]
 * @tparam StreamT   A type of the stream, must be template class with at least
 *                   one parameter for the type. [`std::basic_iostream`]
 * @tparam ByteT     The byte type, should be the same as the first type of
 *                   `StreamT`. [`char`]
 * @tparam StreamTs  Any other type parameters for `StreamT`.
 */
template<std::endian tEndian = std::endian::native,
         template<typename, typename...> typename StreamT = std::basic_iostream,
         typename ByteT = char, typename... StreamTs>
class BinaryStream
{
public:
    /// The stream type of this `BinaryStream` instance.
    using Stream = StreamT<ByteT, StreamTs...>;

    /// The byte type of this `BinaryStream` instance.
    using Byte = ByteT;

    /// The `Binary` instance of this `BinaryStream` instance.
    using BinaryT = Binary<tEndian, Byte>;

    /// The `BinaryString` instance of this `BinaryStream` instance.
    template<typename CharT, typename CharTraits = std::char_traits<CharT>>
    using BinaryStringT = BinaryString<Byte, CharT, CharTraits>;

    /// The endian of this `BinaryStream` instance.
    static constexpr auto endian() -> std::endian { return tEndian; }

    /**
     * @brief The `BinaryStream` constructor.
     *
     * @param stream  A reference to a stream type, like `std::stringstream` or
     *                `std::fstream`.
     */
    BinaryStream(Stream& stream) :
        mStream(stream)
    {

    }

    /// Default copy constructor.
    BinaryStream(BinaryStream const&) = default;

    /// Default move constructor.
    BinaryStream(BinaryStream&&) noexcept = default;

    /// Default destructor.
    ~BinaryStream() noexcept = default;

    /// Default copy assignment operator.
    auto operator=(BinaryStream const&) -> BinaryStream& = default;

    /// Default move assignment operator.
    auto operator=(BinaryStream&&) noexcept -> BinaryStream& = default;

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
    requires(InputStream<StreamT, Byte, StreamTs...>)
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
    requires(InputStream<StreamT, Byte, StreamTs...>)
    {
        return BinaryT::template unpack<Ts...>(readRaw(lengthOf<Ts...>()));
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
    template<typename CharT, typename CharTraits = std::char_traits<CharT>>
    auto readString(std::size_t length, std::string_view encoding = "UTF-8")
        -> std::basic_string<CharT>
    requires(InputStream<StreamT, Byte, StreamTs...>)
    {
        return BinaryStringT<CharT, CharTraits>::decode(readRaw(length),
                                                        encoding);
    }

    /**
     * @brief Write a range of bytes to the stream.
     *
     * @note This requires the stream to be an @ref scppl::OutputStream.
     *
     * @param data  The bytes to write to the stream.
     */
    void writeRaw(RangeOf<Byte> auto data)
    requires(OutputStream<StreamT, Byte, StreamTs...>)
    {
        mStream.write(std::ranges::data(data), std::ranges::size(data));
    }

    /**
     * @brief Write types to a stream.
     *
     * @note This requires the stream to be an @ref scppl::OutputStream.
     *
     * @sa scppl::Binary::pack()
     *
     * @tparam Ts  The types to write to the stream, must be `Packable`.
     *
     * @param types  The values to write to the stream.
     */
    template<Packable... Ts>
    void write(Ts... types)
    requires(OutputStream<StreamT, Byte, StreamTs...>)
    {
        writeRaw(BinaryT::template pack<Ts...>(types...));
    }

    /**
     * @brief Encode and write a string to the stream.
     *
     * @tparam CharT       The type to use as character.
     * @tparam CharTraits  The character traits of the character type.
     *
     * @param string    The string to encode and write.
     * @param encoding  The encoding of the string. [`"UTF-8"`]
     */
    template<typename CharT, typename CharTraits = std::char_traits<CharT>>
    void writeString(std::basic_string_view<CharT> string,
                     std::string_view encoding = "UTF-8")
    requires(OutputStream<StreamT, Byte, StreamTs...>)
    {
        writeRaw(BinaryStringT<CharT, CharTraits>::encode(string, encoding));
    }

private:
    Stream& mStream{};
};

/// An alias for `BinaryStream`, defaulting `StreamT` to `std::basic_istream`.
template<std::endian tEndian = std::endian::native,
         template<typename, typename...> typename StreamT = std::basic_istream,
         typename ByteT = char, typename... StreamTs>
using BinaryInputStream = BinaryStream<tEndian, StreamT, ByteT, StreamTs...>;

/// An alias for `BinaryStream`, defaulting `StreamT` to `std::basic_ostream`.
template<std::endian tEndian = std::endian::native,
         template<typename, typename...> typename StreamT = std::basic_ostream,
         typename ByteT = char, typename... StreamTs>
using BinaryOutputStream = BinaryStream<tEndian, StreamT, ByteT, StreamTs...>;

}

#endif
