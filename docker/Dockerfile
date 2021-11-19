FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get -y update && apt-get install -y --no-install-recommends curl gnupg lsb-core software-properties-common \
    && curl -fsSL https://apt.llvm.org/llvm-snapshot.gpg.key|apt-key add - \
    && apt-add-repository "deb http://apt.llvm.org/`lsb_release -c | cut -f2`/ llvm-toolchain-`lsb_release -c | cut -f2`-12 main" \
    && apt-get install -y --no-install-recommends autoconf cmake ninja-build gcc g++ libtool gfortran llvm-12-dev lld-12 clang-12 libopenmpi-dev openmpi-bin git \
    && apt-get autoremove -y --purge \
    && apt-get clean -y \
    && rm -rf /var/lib/apt/lists/*

# Get & install Enzyme
RUN git clone https://github.com/wsmoses/Enzyme.git \
    && cd Enzyme/enzyme \
    && mkdir build && cd build \
    && cmake -G Ninja .. -DCMAKE_BUILD_TYPE=Debug \
    && ninja

RUN update-alternatives --install /usr/bin/clang clang /usr/bin/clang-12 10 --slave /usr/bin/clang++ clang++ /usr/bin/clang++-12 \
    && update-alternatives --install /usr/bin/opt opt /usr/bin/opt-12 10 \
    && update-alternatives --install /usr/bin/lld lld /usr/bin/lld-12 10 \
    && update-alternatives --install /usr/bin/llvm-symbolizer llvm-symbolizer /usr/bin/llvm-symbolizer-12 10

ENV DEBIAN_FRONTEND=
