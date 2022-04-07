// SPDX-FileCopyrightText: 2021-2022 SanderTheDragon <sanderthedragon@zoho.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef SCPPL_BINARY_BINARYSTREAM_HPP_
#define SCPPL_BINARY_BINARYSTREAM_HPP_

#include <bit>
#include <iostream>

#include "scppl/binary/Binary.hpp"
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
     * @brief Read an amount of bytes from the stream into a `std::array`.
     *
     * @note This requires the stream to be an @ref scppl::InputStream.
     *
     * @tparam N  The amount of bytes to read.
     *
     * @return A `std::array` of `N` `Byte`s.
     */
    template<std::size_t N>
    auto readRaw()
        -> std::array<Byte, N>
    requires(InputStream<StreamT, Byte, StreamTs...>)
    {
        std::array<Byte, N> data{};
        mStream.read(std::ranges::data(data), N);

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
        return BinaryT::template unpack<Ts...>(readRaw<lengthOf<Ts...>()>());
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
