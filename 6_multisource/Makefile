all: lib.exe

clean:
	rm -f *.o *.ll *.exe

%.o: %.c
	../dockerscript.sh clang-12 -c -fuse-ld=lld -flto /host/$^ -O2 -ffast-math -o /host/$@

lib.exe: myblas.o multisource.o
	../dockerscript.sh clang-12 -fuse-ld=lld -flto /host/myblas.o /host/multisource.o -O2 -ffast-math -o /host/$@ -Wl,-mllvm=-load=/Enzyme/enzyme/build/Enzyme/ClangEnzyme-12.so

run-%: %.exe
	../dockerscript.sh /host/$^ 3
