# makefile

EXECUTABLE_NAME = project

INC = ../includes
SRC = ../src

OBJ_DIR = objects

HEADERS = $(wildcard $(INC)/*/*.hpp)
SOURCES = $(wildcard $(SRC)/*/*.cpp)
OBJECTS = $(patsubst $(SRC)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

CC = g++
CFLAGS = -lGL -lGLU -lGLEW -lglut

.PHONY: clean build

build: $(OBJECTS) $(HEADERS)
	$(CC) $(OBJECTS) -I $(SRC) -I $(INC) $(CFLAGS) -o $(EXECUTABLE_NAME)

$(OBJ_DIR)/%.o: $(SRC)/%.cpp
	$(CC) -I $(SRC) -I $(INC) $(CFLAGS) -c $< -o $@

clean:
	rm -fR $(OBJECTS) $(EXECUTABLE_NAME)

clean_project:
	rm -fR ${EXECUTABLE_NAME}