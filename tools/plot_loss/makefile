CC = gcc  
TARGET = plot_loss
SRCS = plot.c
OBJS = $(SRCS:.c=.o)
BINDIR = ../../scripts

.PHONY: all clean

all: $(BINDIR)/$(TARGET)

$(BINDIR)/$(TARGET): $(OBJS) | $(BINDIR)
	$(CC) -o $@ $^ -lm

$(BINDIR):
	mkdir -p $(BINDIR)

%.o: %.c
	$(CC) -c -o $@ $<

clean:
	$(RM) $(BINDIR)/$(TARGET) $(OBJS)