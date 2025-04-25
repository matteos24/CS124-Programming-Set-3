

# Makefile for a simple C program


# Compiler to use

CC = gcc


# Compiler flags

CFLAGS = -Wall -g 


# Source files

SRCS = algorithms.c max_heap.c


# Header files

HDRS = main.c algorithms.h max_heap.h


# Object files

OBJS = $(SRCS:.c=.o)


# Executable name

EXEC = partition 


# Default target

all: $(EXEC)


# Compile object files

$(OBJS): %.o: %.c $(HDRS)

	$(CC) $(CFLAGS) -c $< -o $@


# Link object files to create the executable

$(EXEC): $(OBJS)

	$(CC) $(CFLAGS) $^ -o $@ -lm


# Clean build files

clean:

	rm -f $(OBJS) $(EXEC)


# Run the program

run: $(EXEC)

	./$(EXEC)


