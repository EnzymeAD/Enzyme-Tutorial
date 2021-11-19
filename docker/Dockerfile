# Use Alpine Linux as the parent image
FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get -y update

RUN apt-get install -y wget gnupg lsb-core software-properties-common

RUN wget -O key.key https://apt.llvm.org/llvm-snapshot.gpg.key | apt-key add key.key

RUN apt-add-repository "deb http://apt.llvm.org/`lsb_release -c | cut -f2`/ llvm-toolchain-`lsb_release -c | cut -f2`-12 main"

RUN apt-get install -y autoconf cmake ninja-build gcc g++ libtool gfortran llvm-12-dev clang-12 libopenmpi-dev openmpi-bin git

# Get & install Enzyme
RUN git clone https://github.com/wsmoses/Enzyme.git \
    && cd Enzyme/enzyme \
    && mkdir build && cd build \
    && cmake -G Ninja .. -DCMAKE_BUILD_TYPE=Debug \
    && ninja

RUN update-alternatives --install /usr/bin/clang clang /usr/bin/clang-12 10 --slave /usr/bin/clang++ clang++ /usr/bin/clang++-12
RUN update-alternatives --install /usr/bin/opt opt /usr/bin/opt-12 10
RUN update-alternatives --install /usr/bin/llvm-symbolizer llvm-symbolizer /usr/bin/llvm-symbolizer-12 10
