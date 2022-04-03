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
 * @tparam tEndian  The endian of the data. [`std::endian::native`]
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

    BinaryStream(Stream& stream) :
        mStream(stream)
    {

    }

    BinaryStream(BinaryStream const&) = default;
    BinaryStream(BinaryStream&&) noexcept = default;

    ~BinaryStream() noexcept = default;

    auto operator=(BinaryStream const&) -> BinaryStream& = default;
    auto operator=(BinaryStream&&) noexcept -> BinaryStream& = default;

    template<std::size_t N>
    requires(InputStream<StreamT, Byte, StreamTs...>)
    auto readRaw()
        -> std::array<Byte, N>
    {
        std::array<Byte, N> data{};
        mStream.read(std::ranges::data(data), N);

        return data;
    }

    template<typename... Ts>
    requires(InputStream<StreamT, Byte, StreamTs...>)
    auto read()
        -> std::tuple<Ts...>
    {
        return BinaryT::template unpack<Ts...>(readRaw<lengthOf<Ts...>()>());
    }

private:
    Stream& mStream{};
};

}

#endif
