.. SPDX-FileCopyrightText: 2021-2022 SanderTheDragon <sanderthedragon@zoho.com>
..
.. SPDX-License-Identifier: CC-BY-SA-4.0

#####################
Packing and Unpacking
#####################
The most important functionality of this library is packing and unpacking binary data.
This page explains how to do that.

************
Binary Class
************
The :reference:`Binary class` is the class used for packing and unpacking binary data.
This class has 2 template parameters:

- ``tEndian``, a :cppreference:`std::endian <:>` value to define the endian of the data. ``[std::endian::native]``
- ``ByteT``, the type to use as byte. ``[char]``

=======
Packing
=======
The most important function for packing is ``scppl::Binary<>::pack``.
This function takes any :reference:`Packable <traits:PackableTrait>` type and returns a :cppreference:`std::array <:>` of ``ByteT``.

There is also a function ``scppl::Binary<>::toBytes`` with multiple overloads, which converts a single type to binary.

=========
Unpacking
=========
The most important function for unpacking is ``scppl::Binary<>::unpack``.
This function takes multiple :reference:`Unpackable <traits:UnpackableTrait>` types as template parameters and a :cppreference:`std::ranges::range <:>` of ``ByteT`` as argument.
It returns a :cppreference:`std::tuple <:>` of the types given as template parameters.

An overload exists as well which takes references to types and does not return anything (template parameters can be deduced here).

.. important::

   In the unpacking examples there is a ``#ifdef NO_REF``, the true block will use the original ``scppl::Binary<>::unpack``.
   The false block (after ``#else``) uses the overload with references, both give the exact same results.

There is also a function ``scppl::Binary<>:fromBytes`` with multiple overloads, which converts binary into a single type.


********
Examples
********

=================
Fundamental Types
=================
Fundamental types (excluding ``void``) can always be packed and unpacked.

Packing
-------
.. code-block:: cpp
   :class: cb-copy cb-view

   #include <scppl/binary/Binary.hpp>

   auto main(int argc, char* argv[])
       -> int
   {
       unsigned char c = 0x01;
       unsigned short s = 0x23'45;
       unsigned int i = 0x67'89'AB'CD;

       auto data = scppl::Binary<>::pack(c, s, i);

       // Content of `data` will be
       // |c |s    |i          |
       // |01|45 23|CD AB 89 67| little-endian
       // |01|23 45|67 89 AB CD| big-endian

       return 0;
   }

Unpacking
---------
.. code-block:: cpp
   :class: cb-copy cb-view

   #include <vector>

   #include <scppl/binary/Binary.hpp>

   auto main(int argc, char* argv[])
       -> int
   {
       // Big-endian data
       std::vector<char> data =
           { '\x01', '\x23', '\x45', '\x67', '\x89', '\xAB', '\xCD' };

   #ifdef NO_REF
       auto [ c, s, i ] =
           scppl::Binary<std::endian::big>::unpack<unsigned char,
                                                   unsigned short,
                                                   unsigned int>(data);
   #else
       unsigned char c{};
       unsigned short s{};
       unsigned int i{};

       scppl::Binary<std::endian::big>::unpack(data, c, s, i);
   #endif

       // c = 0x01
       // s = 0x23'45
       // i = 0x67'89'AB'CD

       return 0;
   }


===============
Container Types
===============
Container types can be packed and unpacked if their size is known at compile time.
So a :cppreference:`std::array <:>` can be packed/unpacked, but a :cppreference:`std::vector <:>` can not.

Packing
-------
.. code-block:: cpp
   :class: cb-copy cb-view

   #include <array>

   #include <scppl/binary/Binary.hpp>

   auto main(int argc, char* argv[])
       -> int
   {
       std::array<unsigned short, 4> a = { 0x01'23, 0x45'67, 0x89'AB, 0xCD'EF };

       auto data = scppl::Binary<>::pack(a);

       // Content of `data` will be
       // |a[0] |a[1] |a[2] |a[3] |
       // |23 01|67 45|AB 89|EF CD| little-endian
       // |01 23|45 67|89 AB|CD EF| big-endian

       return 0;
   }

Unpacking
---------
.. code-block:: cpp
   :class: cb-copy cb-view

   #include <array>
   #include <vector>

   #include <scppl/binary/Binary.hpp>

   auto main(int argc, char* argv[])
       -> int
   {
       // Big-endian data
       std::vector<char> data =
           { '\x01', '\x23', '\x45', '\x67', '\x89', '\xAB', '\xCD' };

   #ifdef NO_REF
       auto [ a ] =
           scppl::Binary<std::endian::big>::unpack<std::array<unsigned short, 4>>(data);
   #else
       std::array<unsigned short, 4> a{};

       scppl::Binary<std::endian::big>::unpack(data, a);
   #endif

       // a[0] = 0x01'23
       // a[1] = 0x45'67
       // a[2] = 0x89'AB
       // a[3] = 0xCD'EF

       return 0;
   }


==========
Structures
==========
Structures containing a fundamental type, sized container type or structure can be packed as well.
Just note that the alignment may cause problems, the examples show a simple way to work around that.

.. note::

   Non-native endian requires :extern:`Boost PFR` for byte-swapping structure fields, see :building:`Building <scppl Binary>` for more information.

Packing
-------
.. code-block:: cpp
   :class: cb-copy cb-view

   #define SCPPL_CONFIG_BINARY_USE_PFR
   #include <scppl/binary/Binary.hpp>

   // To force alignment on 1 byte
   #pragma pack(push, 1)
   struct S
   {
       unsigned char c{0x01};
       unsigned short s{0x23'45};
       unsigned int i{0x67'89'AB'CD};
   };
   #pragma pack(pop)

   auto main(int argc, char* argv[])
       -> int
   {
       auto data = scppl::Binary<>::pack(S{});

       // Content of `data` will be
       // |.c|.s   |.i         |
       // |01|45 23|CD AB 89 67| little-endian
       // |01|23 45|67 89 AB CD| big-endian

       return 0;
   }

Unpacking
---------
.. code-block:: cpp
   :class: cb-copy cb-view

   #include <vector>

   #define SCPPL_CONFIG_BINARY_USE_PFR
   #include <scppl/binary/Binary.hpp>

   // To force alignment on 1 byte
   #pragma pack(push, 1)
   struct S
   {
       unsigned char c{0x01};
       unsigned short s{0x23'45};
       unsigned int i{0x67'89'AB'CD};
   };
   #pragma pack(pop)

   auto main(int argc, char* argv[])
       -> int
   {
       // Big-endian data
       std::vector<char> data =
           { '\x01', '\x23', '\x45', '\x67', '\x89', '\xAB', '\xCD' };

   #ifdef NO_REF
       auto [ s ] = scppl::Binary<std::endian::big>::unpack<S>(data);
   #else
       S s{};

       scppl::Binary<std::endian::big>::unpack(data, s);
   #endif

       // s.c = 0x01
       // s.s = 0x23'45
       // s.i = 0x67'89'AB'CD

       return 0;
   }
