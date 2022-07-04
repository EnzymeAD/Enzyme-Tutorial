all: lib.exe

clean:
	rm -f *.o *.ll *.exe

%.o: %.c
	../dockerscript.sh clang-12 -c /host/$^ -O2 -Xclang -load -Xclang /Enzyme/enzyme/build/Enzyme/ClangEnzyme-12.so -ffast-math -o /host/$@

lib.exe: myblas.o multisource.o
	../dockerscript.sh clang-12 /host/myblas.o /host/multisource.o -O2 -Xclang -load -Xclang /Enzyme/enzyme/build/Enzyme/ClangEnzyme-12.so -ffast-math -o /host/$@

run-%: %.exe
	../dockerscript.sh /host/$^ 3
