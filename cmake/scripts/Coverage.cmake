# SPDX-FileCopyrightText: 2021-2022 SanderTheDragon <sanderthedragon@zoho.com>
#
# SPDX-License-Identifier: MIT

macro(add_coverage AC_TARGET)
    if(SCPPL_BUILD_COVERAGE)
        target_compile_options(${AC_TARGET}
                               PUBLIC --coverage -fno-inline -fno-inline-small-functions -fno-default-inline -g -O0)

        target_link_options(${AC_TARGET}
                            PUBLIC --coverage)
    endif()
endmacro()
