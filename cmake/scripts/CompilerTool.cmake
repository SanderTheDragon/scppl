# SPDX-FileCopyrightText: 2021-2022 SanderTheDragon <sanderthedragon@zoho.com>
#
# SPDX-License-Identifier: MIT

macro(compiler_tool CT_VAR CT_CMAKE_VAR)
    cmake_parse_arguments(CT
                          "DEFAULT"
                          "DEFAULT_EXE;NAME;PREFIX"
                          "DEFAULT_ARGS;EXTRA_CMAKE_VARS"
                          ${ARGN})

    if(DEFINED CT_PREFIX)
        set(CT_PREFIX "${CT_PREFIX}_")
    endif()

    option(${CT_PREFIX}TOOL_${CT_VAR} "Enable `${CT_NAME}` [${CT_DEFAULT}]" ${CT_DEFAULT})
    set(${CT_PREFIX}TOOL_${CT_VAR}_EXE ${CT_DEFAULT_EXE} CACHE STRING "`${CT_NAME}` executable [${CT_DEFAULT_EXE}]")
    set(${CT_PREFIX}TOOL_${CT_VAR}_ARGS ${CT_DEFAULT_ARGS} CACHE STRING "`${CT_NAME}` executable arguments [${CT_DEFAULT_ARGS}]")

    if(${CT_PREFIX}TOOL_${CT_VAR})
        set(${CT_CMAKE_VAR} ${${CT_PREFIX}TOOL_${CT_VAR}_EXE} ${${CT_PREFIX}TOOL_${CT_VAR}_ARGS})
        foreach(CT_EXTRA_CMAKE_VAR ${CT_EXTRA_CMAKE_VARS})
            set(${CT_EXTRA_CMAKE_VAR} ${${CT_PREFIX}TOOL_${CT_VAR}_EXE} ${${CT_PREFIX}TOOL_${CT_VAR}_ARGS})
        endforeach()
    else()
        unset(${CT_CMAKE_VAR})
        foreach(CT_EXTRA_CMAKE_VAR ${CT_EXTRA_CMAKE_VARS})
            unset(${CT_EXTRA_CMAKE_VAR})
        endforeach()
    endif()
endmacro()
