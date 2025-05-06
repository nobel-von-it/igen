CC = gcc
LIBS = 
INCLUDES = 
LDFLAGS = -lm

CFLAGS = -W -Wall -Wextra -O2 -g

SRCS = main.c
OBJS = $(SRCS:.c=.o)

TARGET = igen

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
