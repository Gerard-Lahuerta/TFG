CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = generator
SRCS = generator.c
OBJS = $(SRCS:.c=.o)
BINDIR = ../../scripts

.PHONY: all clean

all: $(BINDIR)/$(TARGET)

$(BINDIR)/$(TARGET): $(OBJS) | $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $^ -lm

$(BINDIR):
	mkdir -p $(BINDIR)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(BINDIR)/$(TARGET) $(OBJS)