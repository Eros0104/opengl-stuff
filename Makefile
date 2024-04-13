APP_NAME = myApp
BUILD_DIR = ./bin
C_FILES = ./src/*.cpp ./src/*.c

APP_INCLUDES:= -I./src/vendors/GLFW -I./src/vendors/glad -I./src/vendors/KHR -framework Cocoa -framework OpenGL -framework IOKit
APP_LINKERS:= -L./src/vendors/GLFW/lib -lglfw3

all: build run

build:
	mkdir -p $(BUILD_DIR)
	clang++ -o $(BUILD_DIR)/$(APP_NAME) $(C_FILES) $(APP_INCLUDES) $(APP_LINKERS)

run:
	./$(BUILD_DIR)/$(APP_NAME)