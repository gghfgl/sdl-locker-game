# $@ : target filename.
# $* : target filename without file extension.
# $< : first prerequisite filename.
# $^ : filename of all prerequisite, separated by space, discard duplicates.
# $+ : similar to $^, but includes duplicates.
# $? : names of all prerequisites that are newer than the target, separated by space.

CXX      := -c++ -std=c++11
CXXFLAGS := -pedantic-errors -Wall -Werror -O3 -g
LDFLAGS  := -L/usr/lib -lstdc++ -lm	-framework SDL2 -framework SDL2_image -framework SDL2_ttf -framework SDL2_mixer
BUILD    := ./build
OBJ_DIR  := $(BUILD)/objects
APP_DIR  := $(BUILD)/apps
TARGET   := a.out
INCLUDE  := -Iinclude/ -I/Library/Frameworks/SDL2.framework/Headers -I/Library/Frameworks/SDL2_image.framework/Headers -I/Library/Frameworks/SDL2_ttf.framework/Headers -I/Library/Frameworks/SDL2_mixer.framework/Headers
SRC      :=                         \
	src/main.cpp	           			\
	#$(wildcard src/*.cpp)           \

OBJECTS := $(SRC:%.cpp=$(OBJ_DIR)/%.o)

all: build $(APP_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(LDFLAGS) -o $(APP_DIR)/$(TARGET) $(OBJECTS)

.PHONY: all build clean

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

clean:
	-rm -rf $(BUILD)/*
