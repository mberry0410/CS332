CC = gcc
CFLAGS = -Wall -g

OBJ = search.o traverse.o display.o

search: $(OBJ)
	$(CC) $(CFLAGS) -o search $(OBJ)

search.o: search.c traverse.h display.h
	$(CC) $(CFLAGS) -c search.c

traverse.o: traverse.c traverse.h display.h
	$(CC) $(CFLAGS) -c traverse.c

display.o: display.c display.h
	$(CC) $(CFLAGS) -c display.c

clean:
	rm -f *.o search