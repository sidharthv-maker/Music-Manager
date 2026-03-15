CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iheaderfiles
SRCS = src/album.c\
	   src/files.c\
	   src/main.c\
	   src/queue.c
OBJS = $(SRCS:.c=.o)
TARGET = c_unplugged
all: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)
src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJS) $(TARGET)
