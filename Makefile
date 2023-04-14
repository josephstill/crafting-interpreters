CXX:=g++
BIN:=cpplox

INC_DIR:=./include
SRC_DIR:=./source
OBJ_DIR:=./object
BIN_DIR:=./bin

SRC_LIST:=$(shell find $(SRC_DIR) -name '*.cpp')
OBJ_LIST:=$(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_LIST))

CXX_FLAGS:=-I$(INC_DIR)

TARGET=$(BIN_DIR)/$(BIN)

all: $(TARGET)

$(TARGET): $(OBJ_LIST) | $(BIN_DIR)
	$(CXX) $(CXX_FLAGS) $(OBJ_LIST) main.cpp -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXX_FLAGS) -c $< -o $@ 

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

.PHONY: clean
clean:
	rm -Rf $(OBJ_DIR)
	rm -Rf $(BIN_DIR)