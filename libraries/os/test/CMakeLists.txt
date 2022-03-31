# SPDX-FileCopyrightText: 2021-2022 SanderTheDragon <sanderthedragon@zoho.com>
#
# SPDX-License-Identifier: LGPL-3.0-or-later

cmake_minimum_required(VERSION 3.12)


find_package(GTest REQUIRED)


set(TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/FileSystem.cpp"
                 "${CMAKE_CURRENT_SOURCE_DIR}/Main.cpp"
                 "${CMAKE_CURRENT_SOURCE_DIR}/StandardPaths.cpp"
                 "${CMAKE_CURRENT_SOURCE_DIR}/String.cpp"
                 "${CMAKE_CURRENT_SOURCE_DIR}/Utility.cpp")


add_executable(${PROJECT_NAME}Tests ${TEST_SOURCES})

set_target_properties(${PROJECT_NAME}Tests PROPERTIES
                      CXX_STANDARD 20 CXX_EXTENSIONS NO CXX_STANDARD_REQUIRED YES)

target_link_libraries(${PROJECT_NAME}Tests
                      PUBLIC GTest::GTest GTest::Main
                      PUBLIC ${CMAKE_PROJECT_NAME}::${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}Tests
                           PUBLIC ${${PROJECT_NAME}_INCLUDE_DIR}
                           PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

include(Coverage)

add_coverage(${PROJECT_NAME}Tests)


include(CTest)
include(GoogleTest)

gtest_discover_tests(${PROJECT_NAME}Tests)
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME}Tests)
