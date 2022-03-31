.. SPDX-FileCopyrightText: 2021-2022 SanderTheDragon <sanderthedragon@zoho.com>
..
.. SPDX-License-Identifier: CC-BY-SA-4.0

########
Building
########

*************
CMake Options
*************
Other than the regular CMake options, the following are available.

=================
Library Selection
=================
``SCPPL_LIBRARY_BINARY``
    Enable or disable :program:`scppl Binary`. ``[ON]``

``SCPPL_LIBRARY_OS``
    Enable or disable :program:`scppl OS`. ``[ON]``

==============
Extra Building
==============
``SCPPL_BUILD_DOCS``
    Enable or disable building documentation. ``[OFF]``

``SCPPL_BUILD_TESTS``
    Enable or disable building tests. ``[OFF]``

``SCPPL_BUILD_COVERAGE``
    Enable or disable building with coverage testing. ``[OFF]``

==============
Compiler Tools
==============

Clang Tidy
----------
``SCPPL_TOOL_CLANG_TIDY``
    Enable or disable building with :extern:`clang-tidy`. ``[OFF]``

``SCPPL_TOOL_CLANG_TIDY_EXE``
    Define the executable path for :extern:`clang-tidy`. ``["clang-tidy"]``

``SCPPL_TOOL_CLANG_TIDY_ARGS``
    Define extra arguments for :extern:`clang-tidy`. ``[""]``

Include What You Use
--------------------
``SCPPL_TOOL_IWYU``
    Enable or disable building with :extern:`include-what-you-use`. ``[OFF]``

``SCPPL_TOOL_IWYU_EXE``
    Define the executable path for :extern:`include-what-you-use`. ``["include-what-you-use"]``.

``SCPPL_TOOL_IWYU_ARGS``
    Define extra arguments for :extern:`include-what-you-use`. ``["-Xiwyu" "--mapping_file=${CMAKE_SOURCE_DIR}/cmake/tools/googletest.imp"]``.


========================
Library Specific Options
========================
Options for libraries can be found in their own documentation.

.. ifconfig:: enable_binary

   - :building:`scppl Binary <:CMake Options>`

.. ifconfig:: enable_os

   - :building:`scppl OS <:CMake Options>`


****************
Makefile Targets
****************
Depending on the enabled CMake Options, the following targets may exist.

=========
Libraries
=========
Libraries that are not header-only will have a target named ``{Library}``, it will build the shared object.
These targets are included in ``ALL``.

=============
Documentation
=============
Will build the documentation, requires ``SCPPL_BUILD_DOCS`` to be enabled and :extern:`Doxygen` for library documentation and :extern:`Python` 3 with :file:`requirements.txt` installed.

The targets will be named like ``{Library}Documentation`` for all enabled libraries.
A target ``Documentation`` exists for the main documentation.

=====
Tests
=====
Will build the tests, requires ``SCPPL_BUILD_TESTS`` to be enabled and at least one library.
The targets will be named like ``{Library}Tests``, these targets are included in ``ALL`` as well.

=======
Install
=======
The ``install`` target will install the built libraries, headers and CMake config files.
