SRC_DIRS := src
INC_DIRS := include
OBJ_DIR := bin
BIN_DIR := bin
CPP_OBJ_DIR := $(BIN_DIR)
LIBS := -Llib -lsfml-graphics -lsfml-window -lsfml-system

CPP_FILES := $(shell find $(SRC_DIRS) -name '*.cpp')

CPP_OBJS := $(patsubst $(SRC_DIRS)/%.cpp,$(CPP_OBJ_DIR)/%.o,$(CPP_FILES))

CXX := g++

CCFLAGS := -std=c++14 -Wall -Wextra -g $(foreach D,$(INC_DIRS),-I$(D))

EXECUTABLE := $(BIN_DIR)/main


all: $(EXECUTABLE)

$(EXECUTABLE): $(CPP_OBJS)
	$(CXX) $(CCFLAGS) $^ -o $@ $(LIBS)

$(CPP_OBJ_DIR)/%.o: $(SRC_DIRS)/%.cpp
	$(CXX) $(CCFLAGS) -c $< -o $@

run: $(EXECUTABLE)
	./bin/main $(ARGS)

debug: $(EXECUTABLE)
	gdb ./bin/main $(ARGS)

clean:
	rm -f $(EXECUTABLE) $(CPP_OBJS)
