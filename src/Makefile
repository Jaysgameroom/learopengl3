CFLAGS = -Wall -I/home/josiah/code/learnopengl3/Include/ -L/home/josiah/code/learnopengl3/Libs

# Libraries
LIBS = -l:libglfw3.a -ldl -lm

# Source files
SRC = helloWindow.cpp glad.c

# Target executable
TARGET = out

# Default rule
all: $(TARGET)

# Build target
$(TARGET): $(SRC)
	g++ $(CFLAGS) $(SRC) -o $(TARGET) $(LIBS)

# Clean
clean:
	rm -f $(TARGET)

