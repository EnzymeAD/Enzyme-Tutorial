# Use Alpine Linux as the parent image
FROM alpine:3.14.3

ENV DEBIAN_FRONTEND=noninteractive

# Update OS packages
RUN apk update \
    && apk add gcc cmake ninja \
    && apk add git \
    && apk add gfortran \
    && apk add g++ \
    && apk add python3 \
    && apk add perl \
    && apk add libelf \
    && apk add libffi-dev \
    && apk add elfutils-dev \
    && apk add make

# Change directory
RUN cd home

# Get & install LLVM 12 release
RUN git clone https://github.com/llvm/llvm-project.git \
    && cd llvm-project \
    && git checkout release/12.x \
    && mkdir build \
    && cd build \
    && cmake -G Ninja ../llvm \
        -DCMAKE_BUILD_TYPE=Release \
        -DLLVM_TARGETS_TO_BUILD="host" \
        -DLLVM_ENABLE_PROJECTS="clang;openmp;parallel-libs" \
        -DLLVM_ENABLE_PLUGINS=ON \
        -DLLVM_ENABLE_ASSERTIONS=ON \
    && ninja \
    && cd ../..

# Get & install Open MPI 4.1
RUN wget https://download.open-mpi.org/release/open-mpi/v4.1/openmpi-4.1.1.tar.gz \
    && tar -xf openmpi-4.1.1.tar.gz \
    && rm openmpi-4.1.1.tar.gz \
    && cd openmpi-4.1.1 \
    && mkdir build \
    && ./configure --prefix=/home/openmpi-4.1.1/build \
    && make -j \
    && make install \
    && cd ..

# Get & install Enzyme
RUN git clone https://github.com/wsmoses/Enzyme.git \
    && cd Enzyme/enzyme \
    && mkdir build && cd build \
    && cmake -G Ninja .. \
        -DLLVM_DIR=/home/llvm-project/build/lib/cmake/llvm \
    && ninja
