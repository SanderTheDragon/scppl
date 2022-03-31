.. SPDX-FileCopyrightText: 2021-2022 SanderTheDragon <sanderthedragon@zoho.com>
..
.. SPDX-License-Identifier: CC-BY-SA-4.0

########
Building
########
.. note::

   Main building instructions are in :building:`scppl Index`.

*************
CMake Options
*************

====
UNIX
====
``SCPPL_CONFIG_OS_SAVE_PWD_HOME``
    If ``$HOME`` is not defined, save the home path from the password file in ``$HOME``. ``[TRUE]``

=====
Linux
=====
``SCPPL_CONFIG_OS_CACHE_XDG_USERDIRS``
    Store the paths from the XDG user directories in memory (uses more memory instead of IO and CPU). ``[TRUE]``

``SCPPL_CONFIG_OS_CACHE_XDG_RUNTIME_DIR_FALLBACK``
    Save the fallback for ``XDG_RUNTIME_DIR`` so that following calls will return the same directory. ``[TRUE]``
