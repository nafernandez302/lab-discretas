TARGET = main
SRCS = APIG24.c main.c
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
K5_PATH = examples/K5.txt
K5_1_PATH = examples/K5masunoslados.txt

OBJS = $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

test:
	$(CC) $(CFLAGS) tests/test_1.c -c -o tests/test_1.o
	$(CC) $(CFLAGS) APIG24.o tests/test_1.o -o tests/test_1
	./tests/test_1 < $(K5_1_PATH)

k5:
	./$(TARGET) < $(K5_PATH)
clean:
	rm -f $(OBJS) $(TARGET)