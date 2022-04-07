# SPDX-FileCopyrightText: 2021-2022 SanderTheDragon <sanderthedragon@zoho.com>
#
# SPDX-License-Identifier: CC0-1.0

FROM ubuntu:jammy

ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=Etc/UTC

RUN apt update -y
RUN apt install -y --no-install-recommends bison build-essential flex cmake git googletest clang-tidy-14 iwyu valgrind libgtest-dev libicu-dev python3 python3-pip

RUN pip3 install Sphinx furo breathe sanderthedragon-sphinxext gcovr==5.0

# Install doxygen
RUN cd /root && \
    git clone https://github.com/doxygen/doxygen && \
    mkdir -p doxygen/build && \
    cd doxygen/build && \
    cmake .. -DCMAKE_BUILD_TYPE=Release && \
    make && \
    make install

# Install Boost::PFR
RUN cd /root && \
    git clone https://github.com/boostorg/pfr && \
    mkdir -p /usr/include/boost && \
    cp -R pfr/include/boost/* /usr/include/boost
