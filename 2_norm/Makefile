all: norm-O2enzyme.o norm-enzymeO2.o norm-O2enzyme.ll norm-enzymeO2.ll norm-unopt.ll

clean:
	rm -f *.o *.ll

%-unopt.ll: %.c
	../dockerscript.sh clang-12 /host/$^ -O1 -Xclang -disable-llvm-passes -fno-vectorize -fno-slp-vectorize -ffast-math -fno-unroll-loops -o /host/$@ -S -emit-llvm

%-enzymeO2.ll: %-unopt.ll
	../dockerscript.sh opt-12 /host/$^ -load /Enzyme/enzyme/build/Enzyme/LLVMEnzyme-12.so -enzyme -O2 -o /host/$@ -S -enzyme-print-activity

%-O2enzyme.ll: %-unopt.ll
	../dockerscript.sh opt-12 /host/$^ -load /Enzyme/enzyme/build/Enzyme/LLVMEnzyme-12.so -O2 -enzyme -o /host/$@ -S -enzyme-print-activity

%.o: %.ll
	../dockerscript.sh clang-12 -O2 /host/$^ -o /host/$@ -lm

run-%: %.o
	../dockerscript.sh /host/$^ 2000
