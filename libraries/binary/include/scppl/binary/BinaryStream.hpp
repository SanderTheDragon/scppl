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
#include "scppl/binary/BinaryInputStream.hpp"
#include "scppl/binary/BinaryOutputStream.hpp"
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
class BinaryStream :
    public BinaryInputStream<tEndian, StreamT, ByteT, StreamTs...>,
    public BinaryOutputStream<tEndian, StreamT, ByteT, StreamTs...>

{
public:
    /// The `BinaryInputStream` of this `BinaryStream` instance.
    using InputStreamT =
        BinaryInputStream<tEndian, StreamT, ByteT, StreamTs...>;

    /// The `BinaryOutputStream` of this `BinaryStream` instance.
    using OutputStreamT =
        BinaryOutputStream<tEndian, StreamT, ByteT, StreamTs...>;

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

    /**
     * @brief The `BinaryStream` constructor.
     *
     * @param stream  A reference to a stream type, like `std::stringstream` or
     *                `std::fstream`.
     */
    BinaryStream(Stream& stream) :
        InputStreamT(stream),
        OutputStreamT(stream)
    {
        //
    }

    /// Default copy constructor.
    BinaryStream(BinaryStream const&) = default;

    /// Default move constructor.
    BinaryStream(BinaryStream&&) noexcept = default;

    /// Default destructor.
    ~BinaryStream() noexcept override = default;

    /// Default copy assignment operator.
    auto operator=(BinaryStream const&) -> BinaryStream& = default;

    /// Default move assignment operator.
    auto operator=(BinaryStream&&) noexcept -> BinaryStream& = default;

    /**
     * @brief Get the read/write position of this stream.
     *
     * @note This requires the stream to be synchronized.
     *
     * @return The current read/write position.
     */
    auto tell()
        -> std::size_t
    requires(synchronized())
    {
        return InputStreamT::tellInput();
    }

    /**
     * @brief Whether the stream is at the end.
     *
     * @note This requires the stream to be synchronized.
     *
     * @return `true` if the stream is at the end.
     */
    auto eof()
        -> bool
    requires(synchronized())
    {
        return InputStreamT::eofInput();
    }

    /**
     * @brief Move the read position and write position of this stream.
     *
     * @param offset     The amount of bytes to seek from `direction`.
     * @param direction  The direction to search from. [`std::ios::beg`]
     */
    void seek(std::size_t offset,
              std::ios::seekdir direction = std::ios::beg)
    {
        InputStreamT::seekInput(offset, direction);
        OutputStreamT::seekOutput(offset, direction);
    }

    /**
     * @brief Move the read position and write position of this stream from
     *        the begin.
     *
     * @param offset     The amount of bytes to seek from the begin. [`0`]
     */
    void toBegin(std::size_t offset = 0)
    {
        seek(offset, std::ios::beg);
    }

    /**
     * @brief Move the read position and write position of this stream from
     *        the end.
     *
     * @param offset     The amount of bytes to seek from the end. [`0`]
     */
    void toEnd(std::size_t offset = 0)
    {
        seek(offset, std::ios::end);
    }

    /**
     * @brief Move the read position and write position of this stream from
     *        the current position.
     *
     * @param offset     The amount of bytes to seek from the current position.
     *                  [`0`]
     */
    void skip(std::size_t offset = 0)
    {
        seek(offset, std::ios::cur);
    }

private:
    void readPositionChanged() override
    {
        if constexpr(synchronized())
        {
            OutputStreamT::_seekOutput(InputStreamT::tellInput());
        }
    }

    void writePositionChanged() override
    {
        if constexpr(synchronized())
        {
            InputStreamT::_seekInput(OutputStreamT::tellOutput());
        }
    }
};

/// An alias for `BinaryStream`, defaulting `tSynchronized` to `false`.
template<std::endian tEndian = std::endian::native,
         template<typename, typename...> typename StreamT = std::basic_iostream,
         typename ByteT = char, typename... StreamTs>
using UnsynchronizedBinaryStream =
    BinaryStream<tEndian, false, StreamT, ByteT, StreamTs...>;

}

#endif
