# Sort of https://github.com/TheNetAdmin/Makefile-Templates/tree/master/SmallProject
# with some mods. Licensed by them under MIT License.

OBJS	= raytrace.o
SOURCE	= raytrace.cpp
HEADER	= ray.h vec3.h color.h
CC	 = g++
FLAGS	 = -g -c -Wall -Wextra -std=gnu++17
FLAGS_TESTS	 =
LFLAGS	 = 
LFLAGS_TESTS = -IC:\\boost_1_78_0 -LC:\\boost_1_78_0\\lib -lboost_unit_test_framework-mgw11-mt-x64-1_78
BIN_PATH := bin
OBJ_PATH := obj
SRC_PATH := src


TARGET_NAME := raytrace
TESTS_TARGET_NAME := tests
ifeq ($(OS),Windows_NT)
	TARGET_NAME := $(addsuffix .exe,$(TARGET_NAME))
	TESTS_TARGET_NAME := $(addsuffix .exe,$(TESTS_TARGET_NAME))
endif
TARGET := $(BIN_PATH)/$(TARGET_NAME)
TESTS_TARGET := $(BIN_PATH)/$(TESTS_TARGET_NAME)


all: $(OBJS)
	$(CC) -g $(OBJ_PATH)/$(OBJS) -o $(TARGET) $(LFLAGS)

raytrace.o: $(SRC_PATH)/raytrace.cpp
	$(CC) $(FLAGS) $(SRC_PATH)/raytrace.cpp -o $(OBJ_PATH)/raytrace.o -std=gnu++17

tests: $(SRC_PATH)/tests/test_vec3.cpp
	$(CC) $(FLAGS_TESTS) $(LFLAGS_TESTS) $(SRC_PATH)/tests/test_vec3.cpp -o $(TESTS_TARGET)
	$(TESTS_TARGET)

clean:
	rm -f $(OBJ_PATH)/$(OBJS) $(TARGET) $(TESTS_TARGET)