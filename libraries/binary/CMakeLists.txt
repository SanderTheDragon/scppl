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

find_package(BoostPFR)
define_option(SCPPL_CONFIG_BINARY_USE_PFR "Boost.PFR struct iterating"
              DEFAULT ${BoostPFR_FOUND}
              TARGET ${PROJECT_NAME}
              INHERITANCE INTERFACE
              REQUIRES BoostPFR_FOUND)

find_package(ICU COMPONENTS uc)
define_option(SCPPL_CONFIG_BINARY_USE_ICU "ICU string conversion"
              DEFAULT ${ICU_FOUND}
              TARGET ${PROJECT_NAME}
              INHERITANCE INTERFACE
              REQUIRES ICU_FOUND)


set_target_properties(${PROJECT_NAME} PROPERTIES
                      CXX_STANDARD 20 CXX_EXTENSIONS NO CXX_STANDARD_REQUIRED YES)

target_include_directories(${PROJECT_NAME}
                           INTERFACE $<BUILD_INTERFACE:${${PROJECT_NAME}_INCLUDE_DIR}>
                                     $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

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
