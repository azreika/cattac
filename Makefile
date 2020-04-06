TARGET := cattac

SRC_DIR := src
OBJ_DIR := obj

SAT_SRC_DIR := $(SRC_DIR)/sat
SAT_OBJ_DIR := $(OBJ_DIR)/sat

SAT_SRC := $(wildcard $(SAT_SRC_DIR)/*.c)
SAT_OBJ := $(SAT_SRC:$(SAT_SRC_DIR)/%.c=$(SAT_OBJ_DIR)/%.o)

CC := g++
CPPFLAGS := -Iinclude/sat
CFLAGS := -Wall -Werror -std=c++11

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ_DIR)/main.o $(SAT_OBJ)
	$(CC) $^ -o $@

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(SAT_OBJ_DIR)/%.o: $(SAT_SRC_DIR)/%.c | $(SAT_OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(SAT_OBJ_DIR):
	mkdir -p $@

clean:
	$(RM) -r $(SAT_OBJ_DIR)
	$(RM) $(TARGET)
