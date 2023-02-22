all: fwd.o

clean:
	rm -f *.o *.ll

%.o: %.c
	../dockerscript.sh clang-12 /host/$^ -O3 -Xclang -load -Xclang /Enzyme/enzyme/build/Enzyme/ClangEnzyme-12.so -ffast-math -o /host/$@

run-%: %.o
	../dockerscript.sh /host/$^ 3.14
