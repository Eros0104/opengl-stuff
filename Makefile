include config.mk

APP_NAME = myApp
BUILD_DIR = ./bin
C_FILES = ./src/*.cpp ./src/*.c

APP_INCLUDES:= -I$(VENDORS_PATH) -I./src/vendors/glad -I./src/vendors/KHR -framework Cocoa -framework OpenGL -framework IOKit
APP_LINKERS:= -L$(GLFW_LIB_PATH) -l$(GLFW_LIB_NAME)

all: build run

build:
	mkdir -p $(BUILD_DIR)
	clang++ -o $(BUILD_DIR)/$(APP_NAME) $(C_FILES) $(APP_INCLUDES) $(APP_LINKERS)

run:
	./$(BUILD_DIR)/$(APP_NAME)