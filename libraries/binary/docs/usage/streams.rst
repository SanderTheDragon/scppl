.. SPDX-FileCopyrightText: 2021-2022 SanderTheDragon <sanderthedragon@zoho.com>
..
.. SPDX-License-Identifier: CC-BY-SA-4.0

#######
Streams
#######
Binary streams wrap an input and/or output stream and provides function to pack types into and/or unpack types from it.

******************
BinaryStream Class
******************
The :reference:`BinaryStream class` is the class used for binary streams.
This class has 4 template parameters:

- ``tEndian``, a :cppreference:`std::endian <:>` value to define the endian of the data. ``[std::endian::native]``
- ``StreamT``, the type of the stream, should be a templated class with at least on paramter. ``[std::basic_iostream]``
- ``ByteT``, the type to use as byte. ``[char]``
- ``StreamTs``, any other paramters for ``StreamT``.

.. note::

   There are also :reference:`2 aliases <BinaryStream class:aliases>`, for the :reference:`BinaryStream class`, they only define a different default ``StreamT``.

=======
Reading
=======
Reading is done by calling ``read`` with the types to read as template parameters (just like calling ``scppl::Binary<>::unpack``).
The total length of the types is read from the stream and then unpacked.

=======
Writing
=======
Writing is done by calling ``write`` with the types to write as arguments (just like calling ``scppl::Binary<>::pack``).
The data is written to the stream after packing.
