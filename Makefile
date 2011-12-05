CC=g++
CFLAGS = -Wall -g

dnacompress: byteReader.o cmp_filehandler.o main.o cmp_encode.o cmp_decode.o
	$(CC) $(CFLAGS) byteReader.o cmp_decode.o cmp_encode.o cmp_filehandler.o main.o -o dnacompress

main.o: main.cpp cmp_filehandler.h
	$(CC) $(CFLAGS) main.cpp -c 

cmp_filehandler.o: cmp_filehandler.h cmp_filehandler.cpp
	$(CC) $(CFLAGS) cmp_filehandler.cpp -c

cmp_encode.o: cmp_encode.h cmp_encode.cpp
	$(CC) $(CFLAGS) cmp_encode.cpp -c

cmp_decode.o: cmp_decode.h cmp_decode.cpp
	$(CC) $(CFLAGS) cmp_decode.cpp -c

byteReader.o: byteReader.h byteReader.cpp
	$(CC) $(CFLAGS) byteReader.cpp -c

clean:
	rm -f *.o
	rm -f *~
