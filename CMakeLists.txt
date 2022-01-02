# SPDX-FileCopyrightText: 2021-2022 SanderTheDragon <sanderthedragon@zoho.com>
#
# SPDX-License-Identifier: LGPL-3.0-or-later

cmake_minimum_required(VERSION 3.12)

project(scppl
        DESCRIPTION "SanderTheDragon's C++ Libraries"
        LANGUAGES CXX)


list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/scripts")


option(SCPPL_LIBRARY_BINARY "Build the binary interpretation library" ON)

option(SCPPL_BUILD_DOCS "Build documentation" OFF)
option(SCPPL_BUILD_TESTS "Build tests" ON)


include(CompilerTool)

compiler_tool(CLANG_TIDY CMAKE_CXX_CLANG_TIDY
              NAME "clang-tidy"
              PREFIX SCPPL
              DEFAULT OFF
              DEFAULT_EXE "clang-tidy")

compiler_tool(IWYU CMAKE_CXX_INCLUDE_WHAT_YOU_USE
              NAME "include-what-you-use"
              PREFIX SCPPL
              DEFAULT OFF
              DEFAULT_EXE "include-what-you-use"
              DEFAULT_ARGS "-Xiwyu"
                           "--mapping_file=${CMAKE_SOURCE_DIR}/cmake/tools/googletest.imp")


if(SCPPL_BUILD_TESTS)
    find_package(GTest REQUIRED)

    include(CTest)
    enable_testing()
endif()


configure_file("${CMAKE_SOURCE_DIR}/cmake/tools/clang-no-tidy"
               "${CMAKE_BINARY_DIR}/.clang-tidy"
               COPYONLY)


if(SCPPL_LIBRARY_BINARY)
    add_subdirectory("${CMAKE_SOURCE_DIR}/libraries/binary")
endif()
