TARGET = chess

SRCS = main.c field.h field.c figures.h figures.c printer.h printer.c logger.h logger.c
OBJS = $(SRCS:.c=.o)

LDLIBS = -lncursesw -lm

# OJBS = $(OJBS:.h=.o)
CFLAGS = -Wall -g

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	gcc -o $(TARGET) $(SRCS) $(CFLAGS) $(LDLIBS)
	# ./$(TARGET)

clean:
	rm -rf $(TARGET) $(OBJS)
