// SPDX-FileCopyrightText: 2021-2022 SanderTheDragon <sanderthedragon@zoho.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef SCPPL_BINARY_BINARYSTREAM_HPP_
#define SCPPL_BINARY_BINARYSTREAM_HPP_

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
 * @brief Pack data into and unpack data from a stream.
 *
 * @tparam tEndian        The endian of the data. [`std::endian::native`]
 * @tparam tSynchronized  Keep the read and write positions synchronized.
 *                        [`true`]
 * @tparam StreamT        A type of the stream, must be template class with at
 *                        least one parameter for the type.
 *                        [`std::basic_iostream`]
 * @tparam ByteT          The byte type, should be the same as the first type
 *                        of `StreamT`. [`char`]
 * @tparam StreamTs       Any other type parameters for `StreamT`.
 */
template<std::endian tEndian = std::endian::native, bool tSynchronized = true,
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

    /// Whether this `BinaryStream` instance has synchronized positions.
    static constexpr auto synchronized() -> bool { return tSynchronized; }

    /// Is `StreamT` an @ref scppl::InputStream.
    static constexpr bool isInputStream =
        InputStream<StreamT, Byte, StreamTs...>;

    /// Is `StreamT` an @ref scppl::OutputStream.
    static constexpr bool isOutputStream =
        OutputStream<StreamT, Byte, StreamTs...>;

    /// Is `StreamT` an @ref scppl::InputOutputStream.
    static constexpr bool isInputOutputStream =
        InputOutputStream<StreamT, Byte, StreamTs...>;

    /**
     * @brief The `BinaryStream` constructor.
     *
     * @param stream  A reference to a stream type, like `std::stringstream` or
     *                `std::fstream`.
     */
    BinaryStream(Stream& stream) :
        mStream(stream)
    {
        // Synchronize the positions
        synchronizeOutputToInput();
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
     * @brief Get the read position of this stream.
     *
     * @note This requires the stream to be an @ref scppl::InputStream.
     *
     * @return The current read position.
     */
    auto tellInput()
        -> std::size_t
    requires(isInputStream)
    {
        return mStream.tellg();
    }

    /**
     * @brief Get the write position of this stream.
     *
     * @note This requires the stream to be an @ref scppl::OutputStream.
     *
     * @return The current write position.
     */
    auto tellOutput()
        -> std::size_t
    requires(isOutputStream)
    {
        return mStream.tellp();
    }

    /**
     * @brief Get the read/write position of this stream.
     *
     * @note This requires the stream to be an @ref scppl::InputStream or an
     *       @ref scppl::OutputStream, or a synchronized
     *       @ref scppl::InputOutputStream.
     *
     * @return The current read or write position.
     */
    auto tell()
        -> std::size_t
    requires((isInputStream || isOutputStream) &&
             !(isInputOutputStream && !synchronized()))
    {
        if constexpr(InputStream<StreamT, Byte, StreamTs...>)
        {
            return tellInput();
        }
        else if constexpr(OutputStream<StreamT, Byte, StreamTs...>)
        {
            return tellOutput();
        }
    }

    /**
     * @brief Whether the stream is at the end.
     *
     * @return `true` if the stream is at the end.
     */
    auto eof()
        -> bool
    {
        return mStream.eof();
    }

    /**
     * @brief Move the read position of this stream.
     *
     * @note This requires the stream to be an @ref scppl::InputStream.
     *
     * @param offset     The amount of bytes to seek from `direction`. [`0`]
     * @param direction  The direction to search from. [`std::ios::cur`]
     */
    void seekInput(std::size_t offset = 0,
                   std::ios::seekdir direction = std::ios::cur)
    requires(isInputStream)
    {
        _seekInput(offset, direction);
        synchronizeOutputToInput();
    }

    /**
     * @brief Move the write position of this stream.
     *
     * @note This requires the stream to be an @ref scppl::OutputStream.
     *
     * @param offset     The amount of bytes to seek from `direction`. [`0`]
     * @param direction  The direction to search from. [`std::ios::cur`]
     */
    void seekOutput(std::size_t offset = 0,
                    std::ios::seekdir direction = std::ios::cur)
    requires(isOutputStream)
    {
        _seekOutput(offset, direction);
        synchronizeInputToOutput();
    }

    /**
     * @brief Move the read position and/or write position of this stream.
     *
     * @warning If the stream is an @ref scppl::InputOutputStream and it is
     *          synchronized, then the new read position is used as write
     *          position.
     *
     * @param offset     The amount of bytes to seek from `direction`. [`0`]
     * @param direction  The direction to search from. [`std::ios::cur`]
     */
    void seek(std::size_t offset = 0,
              std::ios::seekdir direction = std::ios::cur)
    {
        if constexpr(isInputOutputStream && synchronized())
        {
            _seekInput(offset, direction);
            _seekOutput(tellInput());
        }
        else
        {
            if constexpr(isInputStream)
            {
                _seekInput(offset, direction);
            }

            if constexpr(isOutputStream)
            {
                _seekOutput(offset, direction);
            }
        }
    }

    /**
     * @brief Move the read position and/or write position of this stream from
     *        the begin.
     *
     * @param offset     The amount of bytes to seek from the begin. [`0`]
     */
    void toBegin(std::size_t offset = 0)
    {
        seek(offset, std::ios::beg);
    }

    /**
     * @brief Move the read position and/or write position of this stream from
     *        the end.
     *
     * @param offset     The amount of bytes to seek from the end. [`0`]
     */
    void toEnd(std::size_t offset = 0)
    {
        seek(offset, std::ios::end);
    }

    /**
     * @brief Move the read position to the current write position.
     */
    void synchronizeInputToOutput()
    {
        if constexpr(isInputOutputStream && synchronized())
        {
            _seekInput(tellOutput());
        }
    }

    /**
     * @brief Move the write position to the current read position.
     */
    void synchronizeOutputToInput()
    {
        if constexpr(isInputOutputStream && synchronized())
        {
            _seekOutput(tellInput());
        }
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
    requires(isInputStream)
    {
        std::vector<Byte> data(length);
        mStream.read(std::ranges::data(data), length);

        synchronizeOutputToInput();

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
    requires(isInputStream)
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
    requires(isInputStream)
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
    template<typename CharT, typename CharTraits = std::char_traits<CharT>>
    auto readString(std::size_t length, std::string_view encoding = "UTF-8")
        -> std::basic_string<CharT>
    requires(isInputStream)
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
    requires(isOutputStream)
    {
        mStream.write(std::ranges::data(data), std::ranges::size(data));

        synchronizeInputToOutput();
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
    requires(isOutputStream)
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
    requires(isOutputStream)
    {
        writeRaw(BinaryStringT<CharT, CharTraits>::encode(string, encoding));
    }

private:
    Stream& mStream{};

    /// Actual implementation for `seekInput`.
    void _seekInput(std::size_t offset = 0,
                    std::ios::seekdir direction = std::ios::beg)
    requires(isInputStream)
    {
        mStream.seekg(offset, direction);
    }

    /// Actual implementation for `seekOutput`.
    void _seekOutput(std::size_t offset = 0,
                     std::ios::seekdir direction = std::ios::beg)
    requires(isOutputStream)
    {
        mStream.seekp(offset, direction);
    }
};

/// An alias for `BinaryStream`, defaulting `StreamT` to `std::basic_istream`.
template<std::endian tEndian = std::endian::native, bool tSynchronized = true,
         template<typename, typename...> typename StreamT = std::basic_istream,
         typename ByteT = char, typename... StreamTs>
using BinaryInputStream = BinaryStream<tEndian, tSynchronized,
                                       StreamT, ByteT, StreamTs...>;

/// An alias for `BinaryStream`, defaulting `StreamT` to `std::basic_ostream`.
template<std::endian tEndian = std::endian::native, bool tSynchronized = true,
         template<typename, typename...> typename StreamT = std::basic_ostream,
         typename ByteT = char, typename... StreamTs>
using BinaryOutputStream = BinaryStream<tEndian, tSynchronized,
                                        StreamT, ByteT, StreamTs...>;

/// An alias for `BinaryStream`, defaulting `tSynchronized` to `false`.
template<std::endian tEndian = std::endian::native,
         template<typename, typename...> typename StreamT = std::basic_iostream,
         typename ByteT = char, typename... StreamTs>
using UnsynchronizedBinaryStream =
    BinaryStream<tEndian, false, StreamT, ByteT, StreamTs...>;

/// An alias for `BinaryInputStream`, defaulting `tSynchronized` to `false`.
template<std::endian tEndian = std::endian::native,
         template<typename, typename...> typename StreamT = std::basic_istream,
         typename ByteT = char, typename... StreamTs>
using UnsynchronizedBinaryInputStream =
    BinaryInputStream<tEndian, false, StreamT, ByteT, StreamTs...>;

/// An alias for `BinaryOutputStream`, defaulting `tSynchronized` to `false`.
template<std::endian tEndian = std::endian::native,
         template<typename, typename...> typename StreamT = std::basic_ostream,
         typename ByteT = char, typename... StreamTs>
using UnsynchronizedBinaryOutputStream =
    BinaryOutputStream<tEndian, false, StreamT, ByteT, StreamTs...>;

}

#endif
