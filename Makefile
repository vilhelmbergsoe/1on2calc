CFLAGS=-Wall -Werror -Wextra -O2 -lm
bin=1on2calc

all:
	$(CC) $(CFLAGS) -o $(bin) main.c

run:
	make && ./$(bin) 5000
