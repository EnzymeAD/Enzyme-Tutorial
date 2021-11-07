# Use Alpine Linux as the parent image
FROM alpine:3.14

# Update OS packages
RUN apk update && apk upgrade

# Get LLVM 12 release
RUN git clone https://github.com/llvm/llvm-project.git \
    && cd llvm-project \
    && git checkout release_12/12.x \
    && mkdir build \
    && cd build \
    && cmake -G Ninja ../llvm \
        -DCMAKE_BUILD_TYPE=Release \
        -DLLVM_TARGETS_TO_BUILD="host" \
        -DLLVM_ENABLE_PROJECTS="clang" \
        -DLLVM_ENABLE_PLUGINS=ON \
        -DLLVM_ENABLE_ASSERTIONS=ON \
    && ninja

# Get Open MPI 4.1
RUN wget https://download.open-mpi.org/release/open-mpi/v4.1/openmpi-4.1.1.tar.gz \
    && tar -xvf openmpi-4.1.1.tar.gz \
    && cd openmpi-4.1.1 \
    && ./configure --prefix= \
    && make -j \
    && make install

# Get & install Enzyme
RUN git clone https://github.com/wsmoses/Enzyme.git \
    && cd Enzyme/enzyme \
    && mkdir build && cd build \
    && cmake -G Ninja .. \
        -DLLVM_DIR= \
    && ninja
