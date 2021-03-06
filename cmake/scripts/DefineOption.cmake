# SPDX-FileCopyrightText: 2021-2022 SanderTheDragon <sanderthedragon@zoho.com>
#
# SPDX-License-Identifier: MIT

macro(define_option DO_VAR DO_DESCRIPTION)
    cmake_parse_arguments(DO
                          ""
                          "DEFAULT;TARGET;INHERITANCE"
                          "REQUIRES"
                          ${ARGN})

    option(${DO_VAR} "Enable ${DO_DESCRIPTION}" ${DO_DEFAULT})

    set(DO_VALUE 0)
    if(${DO_VAR})
        set(DO_VALUE 1)
    endif()

    foreach(REQUIREMENT IN ITEMS ${DO_REQUIRES})
        if(NOT ${REQUIREMENT})
            message(FATAL_ERROR "${DO_DESCRIPTION} requires ${REQUIREMENT}")
        endif()
    endforeach()

    if(DEFINED DO_TARGET)
        set(DO_INHERITANCE_OPTIONS PUBLIC PRIVATE INTERFACE)
        if(NOT DEFINED DO_INHERITANCE OR NOT DO_INHERITANCE IN_LIST DO_INHERITANCE_OPTIONS)
            set(DO_INHERITANCE PUBLIC)
        endif()

        target_compile_definitions(${DO_TARGET} ${DO_INHERITANCE} ${DO_VAR}=${DO_VALUE})
    else()
        add_definitions("-D${DO_VAR}=${DO_VALUE}")
    endif()
endmacro()
