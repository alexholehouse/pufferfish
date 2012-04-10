# macro definitions
CC=g++
CFLAGS = -Wall -g -c
OBJECTFILES = byteReader.o cmp_filehandler.o main.o cmp_encode.o cmp_decode.o cmp_ui.o

# makefile body
pufferfish: $(OBJECTFILES)
	$(CC) $(LDFLAGS) $(OBJECTFILES) -o pufferfish

main.o: main.cpp cmp_filehandler.h cmp_encode.h cmp_decode.h
	$(CC) $(CFLAGS) main.cpp

cmp_filehandler.o: cmp_filehandler.h cmp_filehandler.cpp
	$(CC) $(CFLAGS) cmp_filehandler.cpp

cmp_encode.o: cmp_encode.h cmp_encode.cpp
	$(CC) $(CFLAGS) cmp_encode.cpp

cmp_decode.o: cmp_decode.h cmp_decode.cpp
	$(CC) $(CFLAGS) cmp_decode.cpp

cmp_ui.o: cmp_ui.h cmp_ui.cpp
	$(CC) $(CFLAGS) cmp_ui.cpp

byteReader.o: byteReader.h byteReader.cpp
	$(CC) $(CFLAGS) byteReader.cpp

clean:
	rm -f *.o
	rm -f *~
