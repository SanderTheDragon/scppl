// SPDX-FileCopyrightText: 2021-2022 SanderTheDragon <sanderthedragon@zoho.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef SCPPL_BINARY_BINARYOUTPUTSTREAM_HPP_
#define SCPPL_BINARY_BINARYOUTPUTSTREAM_HPP_

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
 * @brief Pack data into a stream.
 *
 * @tparam tEndian   The endian of the data. [`std::endian::native`]
 * @tparam StreamT   A type of the stream, must be template class with at least
 *                   one parameter for the type. [`std::basic_iostream`]
 * @tparam ByteT     The byte type, should be the same as the first type of
 *                   `StreamT`. [`char`]
 * @tparam StreamTs  Any other type parameters for `StreamT`.
 */
template<std::endian tEndian = std::endian::native,
         template<typename, typename...> typename StreamT = std::basic_ostream,
         typename ByteT = char, typename... StreamTs>
requires(OutputStream<StreamT, ByteT, StreamTs...>)
class BinaryOutputStream
{
public:
    /// The stream type of this `BinaryOutputStream` instance.
    using Stream = StreamT<ByteT, StreamTs...>;

    /// The byte type of this `BinaryOutputStream` instance.
    using Byte = ByteT;

    /// The `Binary` instance of this `BinaryOutputStream` instance.
    using BinaryT = Binary<tEndian, Byte>;

    /// The `BinaryString` instance of this `BinaryOutputStream` instance.
    template<typename CharT, typename CharTraits = std::char_traits<CharT>>
    using BinaryStringT = BinaryString<Byte, CharT, CharTraits>;

    /// The endian of this `BinaryOutputStream` instance.
    static constexpr auto endian() -> std::endian { return tEndian; }

    /**
     * @brief The `BinaryOutputStream` constructor.
     *
     * @param stream  A reference to a stream type, like `std::stringstream` or
     *                `std::fstream`.
     */
    BinaryOutputStream(Stream& stream) :
        mStream(stream)
    {
        //
    }

    /// Default copy constructor.
    BinaryOutputStream(BinaryOutputStream const&) = default;

    /// Default move constructor.
    BinaryOutputStream(BinaryOutputStream&&) noexcept = default;

    /// Default destructor.
    virtual ~BinaryOutputStream() noexcept = default;

    /// Default copy assignment operator.
    auto operator=(BinaryOutputStream const&) -> BinaryOutputStream& = default;

    /// Default move assignment operator.
    auto operator=(BinaryOutputStream&&) noexcept
        -> BinaryOutputStream& = default;

    /// Write types to a stream
    template<typename T>
    auto operator<<(T const& variable)
        -> BinaryOutputStream&
    {
        write<T>(variable);

        return *this;
    }

    /**
     * @brief Get the write position of this stream.
     *
     * @return The current write position.
     */
    auto tellOutput()
        -> std::size_t
    {
        return mStream.tellp();
    }

    /**
     * @brief Whether the stream is at the end.
     *
     * @return `true` if the stream is at the end.
     */
    auto eofOutput()
        -> bool
    {
        return mStream.eof();
    }

    /**
     * @brief Move the write position of this stream.
     *
     * @param offset     The amount of bytes to seek from `direction`. [`0`]
     * @param direction  The direction to search from. [`std::ios::beg`]
     */
    void seekOutput(std::size_t offset = 0,
                    std::ios::seekdir direction = std::ios::beg)
    {
        _seekOutput(offset, direction);
        writePositionChanged();
    }

    /**
     * @brief Move the write position of this stream from the begin.
     *
     * @param offset  The amount of bytes to seek from the begin. [`0`]
     */
    void toBeginOutput(std::size_t offset = 0)
    {
        seekOutput(offset, std::ios::beg);
    }

    /**
     * @brief Move the write position of this stream from the end.
     *
     * @param offset  The amount of bytes to seek from the end. [`0`]
     */
    void toEndOutput(std::size_t offset = 0)
    {
        seekOutput(offset, std::ios::end);
    }

    /**
     * @brief Move the write position of this stream from the current position.
     *
     * @param offset  The amount of bytes to seek from the current position.
     *                [`0`]
     */
    void skipOutput(std::size_t offset = 0)
    {
        seekOutput(offset, std::ios::cur);
    }

    /**
     * @brief Write a range of bytes to the stream.
     *
     * @note This requires the stream to be an @ref scppl::OutputStream.
     *
     * @param data  The bytes to write to the stream.
     */
    void writeRaw(RangeOf<Byte> auto data)
    {
        mStream.write(std::ranges::data(data), std::ranges::size(data));
        writePositionChanged();
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
    {
        writeRaw(BinaryStringT<CharT, CharTraits>::encode(string, encoding));
    }

protected:
    /// Actual implementation for `seekOutput`.
    void _seekOutput(std::size_t offset = 0,
                     std::ios::seekdir direction = std::ios::beg)
    {
        mStream.seekp(offset, direction);
    }

    virtual void writePositionChanged()
    {
        //
    }

private:
    Stream& mStream{};
};

}

#endif
