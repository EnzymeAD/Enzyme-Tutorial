all: cache-alias.o cache-noalias.o

clean:
	rm -f *.o *.ll

%-alias.o: %.c
	../dockerscript.sh clang-12 -Rpass=enzyme /host/$^ -O3 -Xclang -load -Xclang /Enzyme/enzyme/build/Enzyme/ClangEnzyme-12.so -ffast-math -o /host/$@

%-noalias.o: %.c
	../dockerscript.sh clang-12 -Rpass=enzyme -DNOALIAS=1 /host/$^ -O3 -Xclang -load -Xclang /Enzyme/enzyme/build/Enzyme/ClangEnzyme-12.so -ffast-math -o /host/$@

run-%: %.o
	../dockerscript.sh /host/$^
