CC = gcc
CFLAGS = -W -Wall
final: count
count: count.o
	$(CC) $(CFLAGS) -o count count.o
%.o: %.c
	$(CC) $(CFLAGS) $< -c
count.o: count.c
clean:
	@rm *.o count