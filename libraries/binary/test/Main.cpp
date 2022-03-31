// SPDX-FileCopyrightText: 2021-2022 SanderTheDragon <sanderthedragon@zoho.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <stdexcept>

#include <gtest/gtest.h>

#if SCPPL_CONFIG_BINARY_USE_ICU
#include <unicode/uclean.h>
#include <unicode/ucnv.h>
#include <unicode/urename.h>
#include <unicode/utypes.h>
#endif

class Environment : public testing::Environment
{
public:
    void SetUp() override
    {
        if constexpr(SCPPL_CONFIG_BINARY_USE_ICU)
        {
            UErrorCode error{};

            u_init(&error);
            if (U_FAILURE(error))
                throw std::runtime_error(u_errorName(error));
        }
    }

    void TearDown() override
    {
        if constexpr(SCPPL_CONFIG_BINARY_USE_ICU)
        {
            ucnv_flushCache();
            u_cleanup();
        }
    }
};

auto main(int argc, char* argv[])
    -> int
{
    testing::InitGoogleTest(&argc, argv);

    // NOLINTNEXTLINE(cppcoreguidelines-owning-memory): `new` is required here
    testing::AddGlobalTestEnvironment(new Environment());

    return RUN_ALL_TESTS();
}
