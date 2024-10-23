# Compiler
CC = gcc

CFLAGS = -Wall -g

INCLUDES = -I ./includes -I D:\C_libs\mingw64\include  #Hard Linked

LDFLAGS = -L D:\C_libs\mingw64\lib -lraylib -lopengl32 -lgdi32 -lwinmm

SRC = main.c engine.c loader.c
OBJ = $(SRC:.c=.o)
TARGET = Engine

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean rule to remove generated files
clean:
	rm -f $(OBJ) $(TARGET)
