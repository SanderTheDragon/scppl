// SPDX-FileCopyrightText: 2021-2022 SanderTheDragon <sanderthedragon@zoho.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <algorithm>
#include <cstddef>
#include <ranges>
#include <sstream>
#include <string>
#include <utility>

#include <gtest/gtest.h>

#include "scppl/binary/BinaryStream.hpp"

#include "Data.hpp"
#include "Types.hpp"
#include "Utility.hpp"
#include "Values.hpp"

template<std::size_t... Ns>
auto toStream(ByteArray<Ns>... datas)
    -> std::istringstream
{
    auto data = combineArrays(datas...);

    std::string string{};
    string.resize((Ns + ...));

    std::ranges::copy(std::ranges::begin(data), std::ranges::end(data),
                      std::ranges::begin(string));

    std::istringstream stringstream(string);
    stringstream.seekg(0);

    return std::move(stringstream);
}

template<typename T1, typename... Ts>
void assertAllEqual(T1 value, Ts... values)
{
    auto assertTwoEqual = [](auto lhs, auto rhs) -> void
    {
        ASSERT_EQ(lhs, rhs);
    };

    (assertTwoEqual(value, values), ...);
}

template<typename StringstreamT, typename StreamT>
void assertInput(StringstreamT& stringstream, StreamT& stream,
                 std::size_t position)
{
    if constexpr(!StreamT::isOutputStream || StreamT::synchronized())
    {
        assertAllEqual(stringstream.tellg(), stream.tellInput(), stream.tell(),
                       position);
    }
    else
    {
        assertAllEqual(stringstream.tellg(), stream.tellInput(),
                       position);
    }
}

template<typename StringstreamT, typename StreamT>
void assertOutput(StringstreamT& stringstream, StreamT& stream,
                  std::size_t position)
{
    if constexpr(!StreamT::isInputStream || StreamT::synchronized())
    {
        assertAllEqual(stringstream.tellp(), stream.tellOutput(), stream.tell(),
                       position);
    }
    else
    {
        assertAllEqual(stringstream.tellp(), stream.tellOutput(),
                       position);
    }
}

template<typename StringstreamT, typename StreamT>
void assertInputOutput(StringstreamT& stringstream, StreamT& stream,
                       std::size_t position)
{
    assertAllEqual(stringstream.tellg(), stringstream.tellp(),
                   stream.tellInput(), stream.tellOutput(), stream.tell(),
                   position);
}

TEST(BinaryStreamFunctions, InputBeginEndSeek)
{
    auto stringstream = toStream(DDataLE, DDataLE);
    scppl::BinaryStream stream(stringstream);

    assertInput(stringstream, stream, 0);

    stream.read<D_t, D_t>();
    assertInput(stringstream, stream, 16);

    stream.toBegin();
    assertInput(stringstream, stream, 0);

    stream.toEnd();
    assertInput(stringstream, stream, 16);

    stream.toBegin(8);
    assertInput(stringstream, stream, 8);

    stream.toEnd(-8);
    assertInput(stringstream, stream, 8);
}

TEST(BinaryStreamFunctions, OutputBeginEndSeek)
{
    std::ostringstream stringstream{};
    scppl::BinaryStream stream(stringstream);

    assertOutput(stringstream, stream, 0);

    stream.write(D, D);
    assertOutput(stringstream, stream, 16);

    stream.toBegin();
    assertOutput(stringstream, stream, 0);

    stream.toEnd();
    assertOutput(stringstream, stream, 16);

    stream.toBegin(8);
    assertOutput(stringstream, stream, 8);

    stream.toEnd(-8);
    assertOutput(stringstream, stream, 8);
}

TEST(BinaryStreamFunctions, InputOutputBeginEndSeek)
{
    std::stringstream stringstream{};
    scppl::BinaryStream stream(stringstream);

    assertInputOutput(stringstream, stream, 0);

    stream.write(D, D);
    assertInputOutput(stringstream, stream, 16);

    stream.toBegin();
    assertInputOutput(stringstream, stream, 0);

    stream.read<D_t, D_t>();
    assertInputOutput(stringstream, stream, 16);

    stream.toBegin();
    assertInputOutput(stringstream, stream, 0);

    stream.toEnd();
    assertInputOutput(stringstream, stream, 16);

    stream.toBegin(8);
    assertInputOutput(stringstream, stream, 8);

    stream.toEnd(-8);
    assertInputOutput(stringstream, stream, 8);

    stream.seekInput(4);
    assertInputOutput(stringstream, stream, 12);

    stream.seekOutput(4);
    assertInputOutput(stringstream, stream, 16);
}

TEST(BinaryStreamFunctions, UnsynchronizedInputOutputBeginEndSeek)
{
    std::stringstream stringstream{};
    scppl::UnsynchronizedBinaryStream<> stream(stringstream);

    assertInput(stringstream, stream, 0);
    assertOutput(stringstream, stream, 0);

    stream.write(D, D);
    assertInput(stringstream, stream, 0);
    assertOutput(stringstream, stream, 16);

    stream.toBegin();
    assertInput(stringstream, stream, 0);
    assertOutput(stringstream, stream, 0);

    stream.read<D_t, D_t>();
    assertInput(stringstream, stream, 16);
    assertOutput(stringstream, stream, 0);

    stream.toEnd();
    assertInput(stringstream, stream, 16);
    assertOutput(stringstream, stream, 16);

    stream.toBegin(8);
    assertInput(stringstream, stream, 8);
    assertOutput(stringstream, stream, 8);

    stream.read<D_t>();
    assertInput(stringstream, stream, 16);
    assertOutput(stringstream, stream, 8);

    stream.seekInput(-8);
    assertInput(stringstream, stream, 8);
    assertOutput(stringstream, stream, 8);

    stream.seekOutput(8);
    assertInput(stringstream, stream, 8);
    assertOutput(stringstream, stream, 16);
}
