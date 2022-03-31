# SPDX-FileCopyrightText: 2021-2022 SanderTheDragon <sanderthedragon@zoho.com>
#
# SPDX-License-Identifier: LGPL-3.0-or-later

cmake_minimum_required(VERSION 3.12)

project(OS
        VERSION 1.0.0
        DESCRIPTION "OS utility library for scppl"
        LANGUAGES CXX)


set(${PROJECT_NAME}_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(${PROJECT_NAME}_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

set(${PROJECT_NAME}_SOURCES "${${PROJECT_NAME}_SOURCE_DIR}/FileSystem.cpp"
                            "${${PROJECT_NAME}_SOURCE_DIR}/StandardPaths.cpp"
                            "${${PROJECT_NAME}_SOURCE_DIR}/String.cpp"
                            "${${PROJECT_NAME}_SOURCE_DIR}/Utility.cpp")


add_library(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCES})
add_library(${CMAKE_PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})


include(DefineOption)

define_option(SCPPL_CONFIG_OS_CACHE_XDG_USERDIRS "store XDG userdirs in memory"
              DEFAULT TRUE
              TARGET ${PROJECT_NAME}
              INHERITANCE PUBLIC)

define_option(SCPPL_CONFIG_OS_CACHE_XDG_RUNTIME_DIR_FALLBACK "store fallback runtime directory in memory"
              DEFAULT TRUE
              TARGET ${PROJECT_NAME}
              INHERITANCE PUBLIC)

define_option(SCPPL_CONFIG_OS_SAVE_PWD_HOME "save the home path from PWD in the enviroment variable"
              DEFAULT TRUE
              TARGET ${PROJECT_NAME}
              INHERITANCE PUBLIC)


set_target_properties(${PROJECT_NAME} PROPERTIES
                      CXX_STANDARD 20 CXX_EXTENSIONS NO CXX_STANDARD_REQUIRED YES
                      OUTPUT_NAME ${CMAKE_PROJECT_NAME}${PROJECT_NAME}
                      SOVERSION ${PROJECT_VERSION})

target_include_directories(${PROJECT_NAME}
                           PUBLIC $<BUILD_INTERFACE:${${PROJECT_NAME}_INCLUDE_DIR}>
                                  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
                           PRIVATE ${${PROJECT_NAME}_SOURCE_DIR})

include(Coverage)

add_coverage(${PROJECT_NAME})


if(SCPPL_BUILD_TESTS)
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/test")
endif()


if(SCPPL_BUILD_DOCS)
    include(SphinxDoc)

    sphinx_doc("${CMAKE_CURRENT_SOURCE_DIR}/docs"
               TARGET ${PROJECT_NAME}
               DOXYGEN_INPUT "${${PROJECT_NAME}_INCLUDE_DIR}")
endif()


include(GNUInstallDirs)

install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}Targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(EXPORT ${PROJECT_NAME}Targets
        FILE "${PROJECT_NAME}Targets.cmake"
        NAMESPACE ${CMAKE_PROJECT_NAME}::
        DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/cmake/${CMAKE_PROJECT_NAME}")
install(DIRECTORY "${${PROJECT_NAME}_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}"
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
