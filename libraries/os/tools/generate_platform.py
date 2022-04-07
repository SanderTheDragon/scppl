#!/usr/bin/env python3

# SPDX-FileCopyrightText: 2021-2022 SanderTheDragon <sanderthedragon@zoho.com>
#
# SPDX-License-Identifier: MIT

import re
import sys

from datetime import datetime
from pathlib import Path

import requests

from bs4 import BeautifulSoup
from jinja2 import Environment, FileSystemLoader


def get_items(url: str, skip: list[str] = [], rename: dict[str, str] ={},
              extra: dict[str, str] = {}) -> dict[str, dict]:
    html = requests.get(url).text
    document = BeautifulSoup(html, 'lxml')

    result = {}
    for header in document.find_all('h2'):
        if 'id' not in header.attrs:
            continue

        identifier = header.attrs['id']
        if identifier in skip:
            continue
        if identifier in rename.keys():
            identifier = rename[identifier]

        table = header.find_next_sibling()
        while table.name != 'table':
            if table.name == 'h2':
                break

            table = table.find_next_sibling()

        if table.name == 'h2':
            continue

        identifiers = []
        headers = [ head.text for head in table.find_all('th') ]
        for row in table.find('tbody').find_all('tr'):
            columns = row.find_all('td')
            if columns[headers.index('Type')].text == 'Identification':
                ids = columns[headers.index('Macro')].find_all('code')
                ident = '\n'.join([ i.get_text(separator='\n') for i in ids ])

                # Make identifiers with && between them into one identifier
                # it will be split again in `format_defined`
                ident = ident.replace('\n&&\n', '&&')

                for item in ident.split('\n'):
                    stripped = item.strip()
                    if re.fullmatch(r'[0-9A-Za-z_&]+', stripped) is not None:
                        if stripped not in identifiers:
                            identifiers.append(stripped)

        a = header.find('a')
        name = a.text if a is not None else header.text

        extra_defs = {
            'unix': [ 'UNIX' ],
            'linux': [ 'LINUX', 'UNIX' ],
            'bsd': [ 'BSD', 'UNIX' ]
        }

        extras = []
        if identifier in extra.keys():
            extras = extra_defs[extra[identifier]]

        result[identifier] = {
            'name': name,
            'identifiers': identifiers,
            'extra': extras
        }

    return result


def format_macro(string: str) -> str:
    return string.upper().replace('-', '_')


def format_defined(items: list[str], indent: int) -> str:
    def define(item):
        if '&&' not in item:
            return f'defined({item})'

        s = ' && '.join([ define(subitem) for subitem in item.split('&&') ])
        return f'({s})'

    joiner = ' || \\\n' + (' ' * indent)
    return joiner.join([ define(item) for item in items ])


def main() -> int:
    os = get_items('https://sourceforge.net/p/predef/wiki/OperatingSystems',
                   skip=[
                       # All BSDs have their own item
                       'bsd-environment'
                   ],
                   rename={
                       'cygwin-environment': 'cygwin',
                       'gnu-aka-gnuhurd': 'gnuhurd'
                   },
                   # TODO:  Complete this list
                   extra={
                       'android': 'unix',
                       'bsd-os': 'bsd',
                       'cygwin': 'unix',
                       'dragonfly': 'bsd',
                       'freebsd': 'bsd',
                       'gnuhurd': 'unix',
                       'gnukfreebsd': 'bsd',
                       'gnulinux': 'linux',
                       'linux-kernel': 'linux',
                       'macos': 'unix',
                       'minix': 'unix',
                       'netbsd': 'bsd',
                       'openbsd': 'bsd',
                       'unix-environment': 'unix'
                   })

    arch = get_items('https://sourceforge.net/p/predef/wiki/Architectures')

    environment = Environment(loader=FileSystemLoader('.'),
                              keep_trailing_newline=True)
    environment.filters['macrofy'] = format_macro
    environment.filters['defined'] = format_defined
    template = environment.get_template('Platform.hpp.jinja')

    rendered = template.render(os=os, arch=arch, now=datetime.utcnow())

    target = Path('../include/scppl/os')
    with open(target / 'Platform.hpp', 'w') as stream:
        stream.write(rendered)

    return 0


if __name__ == '__main__':
    sys.exit(main())
