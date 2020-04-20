TARGET := cattac

SRC_DIR := src
OBJ_DIR := obj
INC_DIR := include

SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

CC := clang++
CPPFLAGS := -I$(INC_DIR)
CFLAGS := -Wall -Werror -std=c++14 -g
LIBS := -lreadline

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CPPFLAGS) $(CFLAGS) $^ -o $@ $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

clean:
	$(RM) -r $(OBJ_DIR)
	$(RM) $(TARGET)
