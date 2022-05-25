// SPDX-FileCopyrightText: 2021-2022 SanderTheDragon <sanderthedragon@zoho.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <algorithm>
#include <bit>
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

TEST(BinaryStreamFunctions, InputBeginEndSeek)
{
    auto stringstream = toStream(DDataLE, DDataLE);
    scppl::BinaryStream stream(stringstream);

    assertAllEqual(stringstream.tellg(), stream.tellInput(), 0);

    stream.read<D_t, D_t>();
    assertAllEqual(stringstream.tellg(), stream.tellInput(), 16);

    stream.toBegin();
    assertAllEqual(stringstream.tellg(), stream.tellInput(), 0);

    stream.toEnd();
    assertAllEqual(stringstream.tellg(), stream.tellInput(), 16);

    stream.toBegin(8);
    assertAllEqual(stringstream.tellg(), stream.tellInput(), 8);

    stream.toEnd(-8);
    assertAllEqual(stringstream.tellg(), stream.tellInput(), 8);
}

TEST(BinaryStreamFunctions, OutputBeginEndSeek)
{
    std::ostringstream stringstream{};
    scppl::BinaryStream stream(stringstream);

    assertAllEqual(stringstream.tellp(), stream.tellOutput(), 0);

    stream.write(D, D);
    assertAllEqual(stringstream.tellp(), stream.tellOutput(), 16);

    stream.toBegin();
    assertAllEqual(stringstream.tellp(), stream.tellOutput(), 0);

    stream.toEnd();
    assertAllEqual(stringstream.tellp(), stream.tellOutput(), 16);

    stream.toBegin(8);
    assertAllEqual(stringstream.tellp(), stream.tellOutput(), 8);

    stream.toEnd(-8);
    assertAllEqual(stringstream.tellp(), stream.tellOutput(), 8);
}

TEST(BinaryStreamFunctions, InputOutputBeginEndSeek)
{
    std::stringstream stringstream{};
    scppl::BinaryStream stream(stringstream);

    assertAllEqual(stringstream.tellg(), stringstream.tellp(),
                   stream.tellInput(), stream.tellOutput(), stream.tell(), 0);

    stream.write(D, D);
    assertAllEqual(stringstream.tellg(), stringstream.tellp(),
                   stream.tellInput(), stream.tellOutput(), stream.tell(), 16);

    stream.toBegin();
    assertAllEqual(stringstream.tellg(), stringstream.tellp(),
                   stream.tellInput(), stream.tellOutput(), stream.tell(), 0);

    stream.read<D_t, D_t>();
    assertAllEqual(stringstream.tellg(), stringstream.tellp(),
                   stream.tellInput(), stream.tellOutput(), stream.tell(), 16);

    stream.toBegin();
    assertAllEqual(stringstream.tellg(), stringstream.tellp(),
                   stream.tellInput(), stream.tellOutput(), stream.tell(), 0);

    stream.toEnd();
    assertAllEqual(stringstream.tellg(), stringstream.tellp(),
                   stream.tellInput(), stream.tellOutput(), stream.tell(), 16);

    stream.toBegin(8);
    assertAllEqual(stringstream.tellg(), stringstream.tellp(),
                   stream.tellInput(), stream.tellOutput(), stream.tell(), 8);

    stream.toEnd(-8);
    assertAllEqual(stringstream.tellg(), stringstream.tellp(),
                   stream.tellInput(), stream.tellOutput(), stream.tell(), 8);
}

TEST(BinaryStreamFunctions, UnsynchronizedInputOutputBeginEndSeek)
{
    std::stringstream stringstream{};
    scppl::BinaryStream<std::endian::native, false> stream(stringstream);

    assertAllEqual(stringstream.tellg(), stream.tellInput(), 0);
    assertAllEqual(stringstream.tellp(), stream.tellOutput(), 0);

    stream.write(D, D);
    assertAllEqual(stringstream.tellg(), stream.tellInput(), 0);
    assertAllEqual(stringstream.tellp(), stream.tellOutput(), 16);

    stream.toBegin();
    assertAllEqual(stringstream.tellg(), stream.tellInput(), 0);
    assertAllEqual(stringstream.tellp(), stream.tellOutput(), 0);

    stream.read<D_t, D_t>();
    assertAllEqual(stringstream.tellg(), stream.tellInput(), 16);
    assertAllEqual(stringstream.tellp(), stream.tellOutput(), 0);

    stream.toEnd();
    assertAllEqual(stringstream.tellg(), stream.tellInput(), 16);
    assertAllEqual(stringstream.tellp(), stream.tellOutput(), 16);

    stream.toBegin(8);
    assertAllEqual(stringstream.tellg(), stream.tellInput(), 8);
    assertAllEqual(stringstream.tellp(), stream.tellOutput(), 8);

    stream.read<D_t>();
    assertAllEqual(stringstream.tellg(), stream.tellInput(), 16);
    assertAllEqual(stringstream.tellp(), stream.tellOutput(), 8);
}
