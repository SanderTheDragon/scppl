.. SPDX-FileCopyrightText: 2021-2022 SanderTheDragon <sanderthedragon@zoho.com>
..
.. SPDX-License-Identifier: CC-BY-SA-4.0

.. toctree::
   :hidden:

   building.rst
   changelog.rst

#######################################
SanderTheDragon's C++ Libraries (scppl)
#######################################
:program:`scppl` is (or will be) a collection of C++ libraries I wrote because I could not find libraries with the functionalities I needed (or wanted).
The following libraries exist:

.. ifconfig:: enable_binary

   - :project:`scppl Binary`, a C++20 header-only library for packing, unpacking, encoding and decoding binary data.

   .. toctree::
      :hidden:

      {{:project:`scppl Binary`}}

.. ifconfig:: not enable_binary

   - :program:`scppl Binary` (*unavailable*), a C++20 header-only library for packing, unpacking, encoding and decoding binary data.

********
Building
********
First get the source code by either downloading it from :repository:`GitLab`, or clone it using :program:`git`:

.. code-block:: sh
   :class: cb-copy

   git clone https://gitlab.com/SanderTheDragon/scppl

Then run :extern:`CMake` to configure, it is advised to do this out-of-source.
For options see :building:`Building <scppl Index:CMake Options>`.

.. code-block:: sh
   :class: cb-copy

   mkdir build
   cd build
   cmake ..

After it configures correctly, the build can be done, but since there are only header-only libraries now, it will not do anything.
For targets that will do something, see :building:`Building <scppl Index:Makefile Targets>`.

.. code-block:: sh
   :class: cb-copy

   make

Installing is not implemented yet (I realised while writing these documents), it will be added soon.

*******
License
*******
Most code and examples are licensed under :license:`LGPL-3.0-or-later`.
Some code is licensed under :license:`MIT`.

These documents are licensed under :license:`CC-BY-SA-4.0`.

Other files, like configuration files are licensed under :license:`CC0-1.0`.

.. hint::

   This project is :extern:`REUSE` compliant.
