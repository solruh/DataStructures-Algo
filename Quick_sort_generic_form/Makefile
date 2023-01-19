CC = gcc
CFLAGS = -W -Wall

wedishermiutaabiy: quick minfine
quick: quick.o
	$(CC) $(CFLAGS) -o quick quick.o
minfine: minfine.o
	$(CC) $(CFLAGS) -o minfine minfine.o
%.o: %.c
	$(CC) $(CFLAGS) $< -c
quick.o: quick.c
minfine.o: minfine.c
clean:
	@rm *.o quick minfine