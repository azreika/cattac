TARGET := cattac

SRC_DIR := src
OBJ_DIR := obj
INC_DIR := include

SAT_SRC_DIR := $(SRC_DIR)/sat
SAT_OBJ_DIR := $(OBJ_DIR)/sat
SAT_INC_DIR := $(INC_DIR)/sat

SAT_SRC := $(wildcard $(SAT_SRC_DIR)/*.cpp)
SAT_OBJ := $(SAT_SRC:$(SAT_SRC_DIR)/%.cpp=$(SAT_OBJ_DIR)/%.o)

CC := g++
CPPFLAGS := -I$(SAT_INC_DIR)
CFLAGS := -Wall -Werror -std=c++11 -g

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ_DIR)/main.o $(SAT_OBJ)
	$(CC) $(CPPFLAGS) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp $(SAT_SRC)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(SAT_OBJ_DIR)/%.o: $(SAT_SRC_DIR)/%.cpp $(SAT_INC_DIR)/%.h | $(SAT_OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(SAT_OBJ_DIR):
	mkdir -p $@

clean:
	$(RM) -r $(SAT_OBJ_DIR)
	$(RM) $(TARGET)
