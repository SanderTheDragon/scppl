# SPDX-FileCopyrightText: 2021-2022 SanderTheDragon <sanderthedragon@zoho.com>
#
# SPDX-License-Identifier: MIT

set(BoostPFR_PATH "" CACHE STRING "Custom Boost.PFR include path")

set(_BoostPFR_NO_DEFAULT_PATH OFF)
if(BoostPFR_PATH)
    set(_BoostPFR_NO_DEFAULT_PATH ON)
endif()

set(BoostPFR_NO_DEFAULT_PATH ${_BoostPFR_NO_DEFAULT_PATH} CACHE BOOL "Disable searching Boost.PFR headers in default path")
unset(_BoostPFR_NO_DEFAULT_PATH)

set(BoostPFR_NO_DEFAULT_PATH_CMD)
if(BoostPFR_NO_DEFAULT_PATH)
    set(BoostPFR_NO_DEFAULT_PATH_CMD NO_DEFAULT_PATH)
endif()


# Search for the Boost.PFR include directory
find_path(BoostPFR_INCLUDE_DIR pfr.hpp
          HINTS ${BoostPFR_NO_DEFAULT_PATH_CMD}
          PATH_SUFFIXES boost
          PATHS ${BoostPFR_PATH}
          DOC "Where the Boost.PFR headers can be found")

set(BoostPFR_INCLUDE_DIRS "${BoostPFR_INCLUDE_DIR}")


include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(BoostPFR
                                  REQUIRED_VARS BoostPFR_INCLUDE_DIR)


mark_as_advanced(BoostPFR_PATH
                 BoostPFR_NO_DEFAULT_PATH
                 BoostPFR_INCLUDE_DIR)
