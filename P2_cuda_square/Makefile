# Environment Variables
CUDA_PATH ?= /usr/local/cuda-11.2
ENZYME_PATH ?= /home/lpaehler/Work/Dev-Tools/llvm-13/Enzyme/enzyme/build/Enzyme
CLANG_PATH ?= /home/lpaehler/Work/Dev-Tools/llvm-13/llvm-project/build/bin/clang++
SM_VERSION  = 70

CC := $(CLANG_PATH)
CFLAGS = -fno-vectorize -O2 -fno-unroll-loops -fPIC --cuda-path=$(CUDA_PATH) -L$(CUDA_PATH)/lib64 --cuda-gpu-arch=sm_$(SM_VERSION)\
		--no-cuda-version-check -Xclang -load -Xclang $(ENZYME_PATH)
LDFLAGS = -lcudart_static

all: cuda_square

cuda_square: cuda_square.o
	$(CC) $(CFLAGS) cuda_square.o -o cuda_square $(LDFLAGS)