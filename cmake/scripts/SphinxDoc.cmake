# SPDX-FileCopyrightText: 2021-2022 SanderTheDragon <sanderthedragon@zoho.com>
#
# SPDX-License-Identifier: MIT

macro(sphinx_doc SD_DOCS_DIR)
    cmake_parse_arguments(SD
                          ""
                          "SPHINX_BUILDER;TARGET"
                          "DOXYGEN_INPUT"
                          ${ARGN})

    find_program(SPHINX_BUILD sphinx-build
                 PATHS "$ENV{HOME}/.local/bin")

    if(NOT SPHINX_BUILD)
        message(FATAL_ERROR "`sphinx-build` not found")
    endif()

    if(NOT DEFINED SD_SPHINX_BUILDER)
        set(SD_SPHINX_BUILDER "html")
    endif()

    if(DEFINED SD_TARGET)
        string(TOLOWER ${SD_TARGET} SD_LOWER_TARGET)

        set(SD_DOXYGEN_DIR "${CMAKE_BINARY_DIR}/documentation/doxygen/${SD_LOWER_TARGET}")
        set(SD_SPHINX_DIR "${CMAKE_BINARY_DIR}/documentation/sphinx/${SD_LOWER_TARGET}")
        set(SD_OUTPUT_DIR "${CMAKE_BINARY_DIR}/documentation/public/${SD_LOWER_TARGET}")
    else()
        set(SD_DOXYGEN_DIR "${CMAKE_BINARY_DIR}/documentation/doxygen/_")
        set(SD_SPHINX_DIR "${CMAKE_BINARY_DIR}/documentation/sphinx/_")
        set(SD_OUTPUT_DIR "${CMAKE_BINARY_DIR}/documentation/public")
    endif()

    if(DEFINED SD_DOXYGEN_INPUT)
        find_package(Doxygen REQUIRED)

        set(DOXYGEN_CLANG_ASSISTED_PARSING YES)
        set(DOXYGEN_CLANG_OPTIONS "-std=c++20")

        set(DOXYGEN_EXTRACT_STATIC YES)
        set(DOXYGEN_GENERATE_HTML NO)
        set(DOXYGEN_GENERATE_XML YES)
        set(DOXYGEN_MACRO_EXPANSION YES)

        if(DEFINED SD_TARGET)
            get_target_property(SD_INTERFACE_DEFINITIONS ${SD_TARGET} INTERFACE_COMPILE_DEFINITIONS)
            set(DOXYGEN_PREDEFINED ${SD_INTERFACE_DEFINITIONS})
        endif()

        set(DOXYGEN_OUTPUT_DIRECTORY "${SD_DOXYGEN_DIR}")

        doxygen_add_docs(${SD_TARGET}Documentation ${SD_DOXYGEN_INPUT})
    else()
        add_custom_target(${SD_TARGET}Documentation)
    endif()

    configure_file("${SD_DOCS_DIR}/conf.py.in" "${SD_SPHINX_DIR}/conf.py" @ONLY)

    add_custom_command(TARGET ${SD_TARGET}Documentation PRE_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy_directory "${SD_DOCS_DIR}" "${SD_SPHINX_DIR}")

    add_custom_command(TARGET ${SD_TARGET}Documentation POST_BUILD
                       COMMAND ${SPHINX_BUILD} -b ${SD_SPHINX_BUILDER} "${SD_SPHINX_DIR}" "${SD_OUTPUT_DIR}"
                       WORKING_DIRECTORY "${SD_SPHINX_DIR}")
endmacro()
