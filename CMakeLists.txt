# SPDX-FileCopyrightText: 2021-2022 SanderTheDragon <sanderthedragon@zoho.com>
#
# SPDX-License-Identifier: LGPL-3.0-or-later

cmake_minimum_required(VERSION 3.12)

project(scppl
        VERSION 1.0.0
        DESCRIPTION "SanderTheDragon's C++ Libraries"
        LANGUAGES CXX)


list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules"
                              "${CMAKE_SOURCE_DIR}/cmake/scripts")


option(SCPPL_LIBRARY_BINARY "Build the binary interpretation library" ON)
option(SCPPL_LIBRARY_OS "Build the os utility library" ON)

option(SCPPL_BUILD_DOCS "Build documentation" OFF)
option(SCPPL_BUILD_TESTS "Build tests" OFF)
option(SCPPL_BUILD_COVERAGE "Build tests with coverage" OFF)


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


if(SCPPL_BUILD_DOCS)
    include(SphinxDoc)

    sphinx_doc("${CMAKE_CURRENT_SOURCE_DIR}/docs")
endif()


configure_file("${CMAKE_SOURCE_DIR}/cmake/tools/clang-no-tidy"
               "${CMAKE_BINARY_DIR}/.clang-tidy"
               COPYONLY)


if(SCPPL_LIBRARY_BINARY)
    add_subdirectory("${CMAKE_SOURCE_DIR}/libraries/binary")
endif()

if(SCPPL_LIBRARY_OS)
    add_subdirectory("${CMAKE_SOURCE_DIR}/libraries/os")
endif()


include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

write_basic_package_version_file("${CMAKE_BINARY_DIR}/cmake/scpplConfigVersion.cmake"
                                 VERSION ${CMAKE_PROJECT_VERSION}
                                 COMPATIBILITY SameMajorVersion)
configure_package_config_file("${CMAKE_SOURCE_DIR}/cmake/templates/scpplConfig.cmake.in"
                              "${CMAKE_BINARY_DIR}/cmake/scpplConfig.cmake"
                              INSTALL_DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/cmake/${CMAKE_PROJECT_NAME}")

install(FILES "${CMAKE_BINARY_DIR}/cmake/scpplConfig.cmake"
              "${CMAKE_BINARY_DIR}/cmake/scpplConfigVersion.cmake"
        DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/cmake/${CMAKE_PROJECT_NAME}")

# Install additional find modules
install(FILES "${CMAKE_SOURCE_DIR}/cmake/modules/FindBoostPFR.cmake"
        DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/cmake/${CMAKE_PROJECT_NAME}/dependencies")
