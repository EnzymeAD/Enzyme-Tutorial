all: lib.exe

clean:
	rm -f *.o *.ll *.exe

%.o: %.c
	../dockerscript.sh clang-12 -c -fuse-ld=lld -flto /host/$^ -O2 -ffast-math -o /host/$@

lib.exe: myblas.o multisource.o
	../dockerscript.sh clang-12 -fuse-ld=lld -flto /host/myblas.o /host/multisource.o -O2 -ffast-math -o /host/$@ -Wl,-mllvm=-load=/Enzyme/enzyme/build/Enzyme/LLDEnzyme-12.so
# for more recent LLVM versions (tested with v16.0.2) you have to do something like the following (using my tested, non-docker based install, extension to Docker is obvious but
#                                                                                                  I am not posting it since I cannot test it)
#	clang -fuse-ld=lld -flto ./myblas.o ./multisource.o -O2 -ffast-math -o ./$@ -Wl,--load-pass-plugin=../../Enzyme/enzyme/build/Enzyme/LLDEnzyme-16.so

run-%: %.exe
	../dockerscript.sh /host/$^ 3
