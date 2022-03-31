.. SPDX-FileCopyrightText: 2021-2022 SanderTheDragon <sanderthedragon@zoho.com>
..
.. SPDX-License-Identifier: CC-BY-SA-4.0

.. toctree::
   :hidden:

   building.rst

   reference/index.rst

   changelog.rst

   {{:project:`scppl Index`}}

########
scppl OS
########
:program:`scppl OS` is a C++20 library for OS related functions.

*****
Using
*****
To use this library, it should be installed first, after installing use :extern:`CMake` to find it and link to it.
Below is a simple :file:`CMakeLists.txt` which can be used for this library.

.. code-block::
   :class: cb-copy cb-view

   cmake_minimum_required(VERSION 3.12)

   project(Example
           LANGUAGES CXX)

   find_package(scppl REQUIRED COMPONENTS OS)

   set(SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/Example.cpp")

   add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})

   set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
                         CXX_STANDARD 20 CXX_EXTENSIONS NO CXX_STANDARD_REQUIRED YES)

   target_link_libraries(${CMAKE_PROJECT_NAME}
                         PUBLIC scppl::OS)

*******
License
*******
Most code and examples are licensed under :license:`LGPL-3.0-or-later`.
Some code is licensed under :license:`MIT`.

These documents are licensed under :license:`CC-BY-SA-4.0`.

Other files, like configuration files are licensed under :license:`CC0-1.0`.

.. hint::

   This project is :extern:`REUSE` compliant.
