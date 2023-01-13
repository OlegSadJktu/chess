TARGET = chess

SRCS = main.c field.h field.c figures.h figures.c printer.h printer.c 
OBJS = $(SRCS:.c=.o)

LDLIBS = -lncursesw

# OJBS = $(OJBS:.h=.o)
CFLAGS = -Wall

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	gcc -o $(TARGET) $(SRCS) $(CFLAGS) $(LDLIBS)
	# ./$(TARGET)

clean:
	rm -rf $(TARGET) $(OBJS)
