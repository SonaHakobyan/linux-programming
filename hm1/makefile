CC      := g++
CFLAGS  := -g -Wall
TARGET 	:= output
SRCS = main.cpp complex.cpp complex.h
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

clean:
	rm -f $(TARGET) *.o

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@