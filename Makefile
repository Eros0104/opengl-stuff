APP_NAME = myApp
BUILD_DIR = ./bin
C_FILES = ./src/*.c

all: build run

build:
	mkdir -p $(BUILD_DIR)
	clang -o $(BUILD_DIR)/$(APP_NAME) $(C_FILES)

run:
	./$(BUILD_DIR)/$(APP_NAME)