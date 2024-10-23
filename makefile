# Compiler
CC = gcc

# Compiler flags (for warnings, debugging symbols, and raylib support)
CFLAGS = -Wall -g

# Include directories (raylib includes and your own includes)
INCLUDES = -I ./includes -I D:\C_libs\mingw64\include

# Linker flags (for raylib)
LDFLAGS = -L D:\C_libs\mingw64\lib -lraylib -lopengl32 -lgdi32 -lwinmm

# Source files
SRC = main.c engine.c loader.c

# Object files (compiled .o files)
OBJ = $(SRC:.c=.o)

# Executable output file
TARGET = Engine

# Default rule, build the program
all: $(TARGET)

# Rule to link object files and create the final executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(TARGET)

# Rule to compile .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean rule to remove generated files
clean:
	rm -f $(OBJ) $(TARGET)
