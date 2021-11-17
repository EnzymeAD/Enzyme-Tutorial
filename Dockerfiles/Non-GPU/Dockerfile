# Use Alpine Linux as the parent image
FROM ubuntu:21.10

# Update OS packages
RUN apt-get -y update && apt-get -y upgrade

# Get & install LLVM 12 release
#RUN git clone https://github.com/llvm/llvm-project.git \
#    && cd llvm-project \
#    && git checkout release_12/12.x \
#    && mkdir build \
#    && cd build \
#    && cmake -G Ninja ../llvm \
#        -DCMAKE_BUILD_TYPE=Release \
#        -DLLVM_TARGETS_TO_BUILD="host" \
#        -DLLVM_ENABLE_PROJECTS="clang;openmp;parallel-libs" \
#        -DLLVM_ENABLE_PLUGINS=ON \
#        -DLLVM_ENABLE_ASSERTIONS=ON \
#    && ninja \
#    && cd ../..

# Get & install Open MPI 4.1
#RUN wget https://download.open-mpi.org/release/open-mpi/v4.1/openmpi-4.1.1.tar.gz \
#    && tar -xvf openmpi-4.1.1.tar.gz \
#    && cd openmpi-4.1.1 \
#    && ./configure \
#    && make -j \
#    && make install \
#    && cd ..

# Get & install Enzyme
#RUN git clone https://github.com/wsmoses/Enzyme.git \
#    && cd Enzyme/enzyme \
#    && mkdir build && cd build \
#    && cmake -G Ninja .. \
#        -DLLVM_DIR= \
#    && ninja
