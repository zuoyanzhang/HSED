CC := g++
TAR = bin/errorDetect.exe
CPP = src/*.cpp
Include = -lm -lmpfr -I ./include
$(TAR) : $(CPP)
	$(CC) $(CPP) -o $(TAR) $(Include)
.PHONY:
clean:
	rm $(TAR)