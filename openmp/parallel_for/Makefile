CLANG = /home/lpaehler/Work/Dev-Tools/llvm-fortran/f18-llvm-project/build/bin/clang

LLVM_PATH = /home/lpaehler/Work/Dev-Tools/llvm-fortran/f18-llvm-project/build

ENZYME_PATH = /home/lpaehler/Work/AutomaticDifferentiation/Enzyme/build/Enzyme/LLVMEnzyme-13.so
LLVM13_PATH = /home/lpaehler/Work/AutomaticDifferentiation/llvm-project/build

all: omp_parallel_simple.o

clean:
	rm -f *.o *.ll

%.o: %.c
	$(LLVM_PATH)/bin/clang++  -O3 -Xclang -load -Xclang $(ENZYME_PATH) -ffast-math -fopenmp -o /host/$@

run-%: %.o
	../dockerscript.sh /host/$^
