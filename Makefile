TARGET = main
SRCS = APIG24.c main.c
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
K5_PATH = examples/K5.txt

OBJS = $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

k5:
	./$(TARGET) < $(K5_PATH)
clean:
	rm -f $(OBJS) $(TARGET)