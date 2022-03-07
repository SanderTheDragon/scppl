.. SPDX-FileCopyrightText: 2021-2022 SanderTheDragon <sanderthedragon@zoho.com>
..
.. SPDX-License-Identifier: CC-BY-SA-4.0

########
Building
########

.. note::

   Main building instructions are in :building:`scppl Index`.

******************
Optional Libraries
******************
The following libraries are not required to use :program:`scppl Binary`, but certain functionalities will not be available.

=========
Boost PFR
=========
:extern:`Boost PFR` is used to automatically iterate over fields of a structure and byte-swap them.
This is not required when working with native endian.
But non-native endian will require manual byte-swapping without :extern:`Boost PFR`.

===
ICU
===
:extern:`ICU` is required for string encoding and decoding.
Without :extern:`ICU` any call to encode or decode will just return the same data only converted to the return type.


*************
CMake Options
*************

=========
Libraries
=========
- ``SCPPL_CONFIG_BINARY_USE_ICU``: enable using :extern:`ICU`, requires it to be found. ``[${ICU_FOUND}]``
- ``SCPPL_CONFIG_BINARY_USE_PFR``: enable using :extern:`Boost PFR`, requires it to be found. ``[${PFR}]``
