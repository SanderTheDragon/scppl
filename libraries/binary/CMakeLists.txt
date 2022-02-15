# SPDX-FileCopyrightText: 2021-2022 SanderTheDragon <sanderthedragon@zoho.com>
#
# SPDX-License-Identifier: LGPL-3.0-or-later

cmake_minimum_required(VERSION 3.12)

project(Binary
        VERSION 1.0.0
        DESCRIPTION "Binary interpreting library for scppl"
        LANGUAGES CXX)


set(${PROJECT_NAME}_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")


add_library(${PROJECT_NAME} INTERFACE)
add_library(${CMAKE_PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})


include(DefineOption)

find_file(PFR "boost/pfr.hpp")
define_option(SCPPL_CONFIG_BINARY_USE_PFR "PFR struct iterating"
              DEFAULT ${PFR}
              TARGET ${PROJECT_NAME}
              INHERITANCE INTERFACE
              REQUIRES PFR)

find_package(ICU COMPONENTS uc)
define_option(SCPPL_CONFIG_BINARY_USE_ICU "ICU string conversion"
              DEFAULT ${ICU_FOUND}
              TARGET ${PROJECT_NAME}
              INHERITANCE INTERFACE
              REQUIRES ICU_FOUND)


target_include_directories(${PROJECT_NAME}
                           INTERFACE ${${PROJECT_NAME}_INCLUDE_DIR})

if(SCPPL_CONFIG_BINARY_USE_ICU)
    target_link_libraries(${PROJECT_NAME}
                          INTERFACE ICU::uc)
endif()


if(SCPPL_BUILD_TESTS)
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/test")
endif()


if(SCPPL_BUILD_DOCS)
    include(SphinxDoc)

    sphinx_doc("${CMAKE_CURRENT_SOURCE_DIR}/docs"
               TARGET ${PROJECT_NAME}
               DOXYGEN_INPUT "${${PROJECT_NAME}_INCLUDE_DIR}")
endif()
