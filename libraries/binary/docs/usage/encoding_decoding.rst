.. SPDX-FileCopyrightText: 2021-2022 SanderTheDragon <sanderthedragon@zoho.com>
..
.. SPDX-License-Identifier: CC-BY-SA-4.0

#####################
Encoding and Decoding
#####################
In addition to packing and unpacking, this library supports encoding and decoding strings.
Encoding and decoding is done using :extern:`ICU`, see :building:`Building <scppl Binary>` for more information.

******************
BinaryString Class
******************
The :reference:`BinaryString class` is the class used for packing and unpacking binary data.
This class has 3 template parameters:

- ``ByteT``, the type to use as byte for the binary data. ``[char]``
- ``CharT``, the type to use as character for strings. ``[char]``
- ``CharTraits``, the character traits for the strings. ``[std::char_traits<CharT>]``

========
Encoding
========
The function to call for encoding is ``scppl::BinaryString<>::encode``.
This function takes a :cppreference:`std::basic_string_view<CharT> <std::string_view:>` as string to encode and a :cppreference:`std::string_view <:>` for the encoding, which defaults to ``"UTF-8"``.
It returns a :cppreference:`std::vector<ByteT> <std::vector:>` containing the encoded string.

========
Decoding
========
The function to call for decoding is ``scppl::BinaryString<>::decode``.
This function takes a :cppreference:`std::ranges::range <:>` of ``ByteT`` to decode and a :cppreference:`std::string_view <:>` for the encoding, which defaults to ``"UTF-8"``.
It returns a :cppreference:`std::basic_string<CharT> <std::string:>` containing the decoded string.


********
Examples
********

========
Encoding
========
.. code-block:: cpp
   :class: cb-copy cb-view

   #include <string>

   #define SCPPL_CONFIG_BINARY_USE_ICU
   #include <scppl/binary/BinaryString.hpp>

   auto main(int argc, char* argv[])
       -> int
   {
       // TeSuTo TeKiSuTo, best Japanese version of TestText I could come up with
       // encoded as UTF-8 here
       std::basic_string<char8_t> text{u8"テストテキスト"};

       // Encode as Shift-JIS
       auto data = scppl::BinaryString<char, char8_t>::encode(text, "Shift-JIS");

       // Content of `data` will be
       // |Te   |Su   |To   |Te   |Ki   |Su   |To   |
       // |83 65|83 58|83 67|83 65|83 4C|83 58|83 67|

       return 0;
   }

========
Decoding
========
.. code-block:: cpp
   :class: cb-copy cb-view

   #include <vector>

   #define SCPPL_CONFIG_BINARY_USE_ICU
   #include <scppl/binary/BinaryString.hpp>

   auto main(int argc, char* argv[])
       -> int
   {
       // Shift-JIS encoded data
       std::vector<char> data = { '\x83', '\x65', '\x83', '\x58',
                                  '\x83', '\x67', '\x83', '\x65',
                                  '\x83', '\x4C', '\x83', '\x58',
                                  '\x83', '\x67' };

       // Decode to UTF-8
       auto text = scppl::BinaryString<char, char8_t>::decode(data, "Shift-JIS");

       // text = u8"テストテキスト"

       return 0;
   }
