# SPDX-FileCopyrightText: 2021-2022 SanderTheDragon <sanderthedragon@zoho.com>
#
# SPDX-License-Identifier: MIT

import os
import re

from pathlib import Path


# URLs
repository_url = 'https://gitlab.com/SanderTheDragon/scppl'
project_repository_url = repository_url + '/-/tree/main/libraries/{}'

is_local = (os.environ.get('GITLAB_CI', 'false').lower() != 'true')

documentation_url = 'https://sanderthedragon.gitlab.io/scppl'
if is_local:
    # There is probably a better way, but this will do for now
    documentation_url = str(Path(__file__).parent.parent
                            / 'build/documentation/public')

project_documentation_url = documentation_url + '/{}index.html'
project_building_url = documentation_url + '/{}building.html'
project_changelog_url = documentation_url + '/{}changelog.html'

# Data
gitlab_icon = '''
    <svg width="65" height="60" viewBox="0 0 210 194" xmlns="http://www.w3.org/2000/svg">
        <path d="m105.0614 193.655 38.64-118.921h-77.28l38.64 118.921Z" fill="#E24329"/>
        <path d="m105.0614 193.6548-38.64-118.921h-54.153l92.793 118.921Z" fill="#FC6D26"/>
        <path d="m12.2685 74.7341-11.742 36.139c-1.071 3.296.102 6.907 2.906 8.944l101.629 73.838-92.793-118.921Z" fill="#FCA326"/>
        <path d="M12.2685 74.7342h54.153l-23.273-71.625c-1.197-3.686-6.411-3.685-7.608 0l-23.272 71.625Z" fill="#E24329"/>
        <path d="m105.0614 193.6548 38.64-118.921h54.153l-92.793 118.921Z" fill="#FC6D26"/>
        <path d="m197.8544 74.7341 11.742 36.139c1.071 3.296-.102 6.907-2.906 8.944l-101.629 73.838 92.793-118.921Z" fill="#FCA326"/>
        <path d="M197.8544 74.7342h-54.153l23.273-71.625c1.197-3.686 6.411-3.685 7.608 0l23.272 71.625Z" fill="#E24329"/>
    </svg>
'''

# Globals
footer_icons = [
    {
        'name': 'GitLab',
        'url': repository_url,
        'html': gitlab_icon,
        'class': 'grayscale'
    }
]

role_mapping = {
    'project': project_documentation_url,
    'building': project_building_url,
    'changelog': project_changelog_url,

    'repository': None,

    'cppreference': 'https://en.cppreference.com/w/cpp/{}',
    'license': 'https://spdx.org/licenses/{}.html',

    'extern': None
}

project_mapping = {
    'scppl Index': '',

    'scppl Binary': 'binary/',
    'scppl OS': 'os/'
}

building_mapping = project_mapping
changelog_mapping = project_mapping

repository_mapping = {
    'GitLab': repository_url,

    'Binary': project_repository_url.format('binary'),
    'OS': project_repository_url.format('os')
}

cppreference_mapping = {
    'Fundamental Types': 'language/types',

    'std::array': 'container/array',
    'std::vector': 'container/vector',

    'std::ranges::range': 'ranges/range',

    'std::string': 'string/basic_string',
    'std::string_view': 'string/basic_string_view',

    'std::endian': 'types/endian',

    'std::tuple': 'utility/tuple'
}

extern_mapping = {
    'CMake': 'https://cmake.org',
    'clang-tidy': 'https://clang.llvm.org/extra/clang-tidy',
    'include-what-you-use': 'https://include-what-you-use.org',
    'REUSE': 'https://reuse.software',

    'Boost PFR':
        'https://www.boost.org/doc/libs/master/doc/html/boost_pfr.html',
    'ICU': 'https://icu.unicode.org/',

    'Doxygen': 'https://www.doxygen.nl',
    'Python': 'https://www.python.org'
}

# TOC does not seem to support anything other than `title <url>`
# So this is my solution, for now at least
# TODO: Maybe create a new TOC directive
def toc_workaround(filename: str) -> None:
    content = ''
    with open(filename, 'r') as stream:
        content = stream.read()

    # TOC only allows URLs with http:// in them, anchors count as well
    def force_http(url: str) -> str:
        if not url.startswith('http'):
            return url + '#http://'

        return url

    # Callback for `re.sub`
    def replace_url(match: re.Match) -> str:
        url = globals()['role_mapping'][match.group(1)]
        directive = match.group(1)
        key = match.group(2)

        if f'{directive}_mapping' in globals():
            mapping = globals()[f'{directive}_mapping']
            if key in mapping.keys():
                return f'{key} <{force_http(url.format(mapping[key]))}>'

        return f'{key} <{force_http(url.format(key))}>'

    content = re.sub('{{:([^:]+):`([^`]+)`}}', replace_url, content)

    with open(filename, 'w') as stream:
        stream.write(content)
