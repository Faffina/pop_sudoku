OUT_NAME=pop_sudoku
SOURCE_FILE := $(shell find ./source -name "*.c")
OBJ_FILE := $(patsubst ./source/%.c, build/%.o, $(SOURCE_FILE))
DEP_FILE := $(patsubst build/%.o, build/%.d, $(OBJ_FILE))
BUILD_FOLDER := $(sort $(dir $(DEP_FILE)) $(dir $(OBJ_FILE)))

all: make_dir $(OUT_NAME)

$(OUT_NAME): $(OBJ_FILE)
	clang -lncurses $^ -o $@

build/%.o: source/%.c
	clang -O3 -march=native -I include -MMD -c $< -o $@

make_dir:
	mkdir -p $(BUILD_FOLDER)

-include $(DEP_FILE)

.PHONY: all make_dir
