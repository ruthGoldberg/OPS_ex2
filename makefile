CC = gcc
OBJECTS_CMP =cmp.o
OBJECTS_COPY =copy.o
FLAGS = -Wall -g

all:cmp copy encode decode stshell

cmp: $(OBJECTS_CMP)

copy: $(OBJECTS_COPY)

encode: encode.o partB.h libA libB
	$(CC) $(FLAGS) encode.o -fPIC -ldl -o encode

decode: decode.o partB.h libA libB 
	$(CC) $(FLAGS) decode.o -fPIC -ldl -o decode

stshell: stshell.o

$(OBJECTS_CMP): cmp.c 
	$(CC) $(FLAGS) -c cmp.c

$(OBJECTS_COPY): copy.c
	$(CC) $(FLAGS) -c copy.c

decode.o:  decode.c partB.h
	$(CC) $(FLAGS) -c decode.c

encode.o:  encode.c partB.h
	$(CC) $(FLAGS) -c encode.c

codeA.o: codeA.c partB.h
	$(CC) $(FLAGS) -c codeA.c

codeB.o: codeB.c partB.h
	$(CC) $(FLAGS) -c codeB.c

libA: partB.h codeA.o 
	$(CC) $(FLAGS) -shared codeA.o -fPIC -o libcodecA.so

libB: partB.h codeB.o
	$(CC) $(FLAGS) -shared codeB.o -fPIC -o libcodecB.so

stshell.o: stshell.c
	$(CC) $(FLAGS) -c stshell.c


.PHONY: clean all

clean:
	rm -f *.o *.so cmp copy encode decode stshell


