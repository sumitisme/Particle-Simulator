# Source file
OBJ1 = main.cpp entity.cpp

# Output file and path
OBJ_NAME = ..\build\prog

# Compiler used
CC = g++

# Include path
INCLUDE_PATH = -I..\include\

# Library path
LIBRARY_PATH = -L..\lib\

# Linkers
LINKERS = -lSDL2 -lSDL2main -lmingw32 -lSDL2_image 

# Compiler flags
COMPILER_FLAGS = 

# Final command

all:	$(OBJ1)
	$(CC) $(OBJ1) $(INCLUDE_PATH) $(LIBRARY_PATH) $(LINKERS) $(COMPILER_FLAGS) -o $(OBJ_NAME)

clear:	
	rm $(OBJ_NAME)
