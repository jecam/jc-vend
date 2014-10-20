########################################################################
# COSC1076 - Advanced Programming Techniques
# Semester 2 2014 Assignment #2
# Full Name        : EDIT HERE
# Student Number   : EDIT HERE
# Course Code      : EDIT HERE
# Program Code     : EDIT HERE
# Start up code provided by Paul Miller and Virginia King
########################################################################

########################################################################
# Move this target to the end of the Makefile to zip up your code 
# when submitting. Please add any additional files you add to your 
# project and delete ones your remove. Do not submit your .dat files, 
# your .bin files, containing directories. We only want the files that 
# are part of your implementation
########################################################################

CC := gcc

BIN := vm
BIN_PATH := ..
SRC_PATH := ../src
SRC_EXT := c
OBJ_PATH := .build

CFLAGS := -Wall -pedantic -Wextra -ansi
DBG_CFLAGS := -g

RM := rm -vf
SHELL := /bin/bash
MEMAPP := valgrind

SOURCES := $(shell find $(SRC_PATH)/ -name '*.$(SRC_EXT)')

OBJECTS := $(SOURCES:$(SRC_PATH)/%.$(SRC_EXT)=%.o)

DIRS := $(addprefix $(OBJ_PATH)/, $(filter-out ./, $(dir $(OBJECTS))))

OBJECTS := $(OBJECTS:%.o=$(OBJ_PATH)/%.o)

DEPS := $(OBJECTS:.o=.d)

.PHONY: debug
debug: CFLAGS += $(DBG_CFLAGS)
debug: all

.PHONY: all
all: dirs $(BIN_PATH)/$(BIN)

$(BIN_PATH)/$(BIN) : $(OBJECTS)
	@echo linking $(BIN_PATH)/$(BIN)
	$(CC) -o $(BIN_PATH)/$(BIN) $(OBJECTS)

.PHONY: clean
clean:
	@echo "Removing dependencies"
	$(RM) $(DEPS)
	@echo "Removing object files"
	$(RM) $(OBJECTS)
	@echo "Removing executable"
	$(CMD_PREFIX)$(RM) $(BIN_PATH)/$(BIN)

.PHONY: dirs
dirs:
	@echo "Creating folders"
ifneq ($(strip $(DIRS)),)
	@mkdir -p $(DIRS)
endif

-include $(DEPS)

# Source file rules
$(OBJECTS): $(OBJ_PATH)/%.o: $(SRC_PATH)/%.$(SRC_EXT)
	@echo "Compiling: $< -> $@"
	$(CC) $(CFLAGS) -MP -MMD -c $< -o $@

# Lists all source files
.PHONY: echosrc
echosrc:
	@echo "Listing source files"
	@echo $(SOURCES)

# Lists all object files
.PHONY: echoobj
echoobj:
	@echo "Listing object files"
	@echo $(OBJECTS)

# Lists all dependencies, can only be done after the dependencies have been generated (ie compiled)
.PHONY: echodeps
echodeps:
	@echo "Listing dependencies"
	@cat $(DEPS)

.PHONY: test
test: all
	$(BIN_PATH)/./$(BIN) $(BIN_PATH)/data/stock.dat $(BIN_PATH)/data/coins.dat

.PHONY: memtest
memtest: all
	$(MEMAPP) $(BIN_PATH)/./$(BIN) $(BIN_PATH)/data/stock.dat $(BIN_PATH)/data/coins.dat

.PHONY: archive
archive:
	zip $(USER) vm_main.c vm_options.c vm_options.h vm_type.h \
	vm_menu.c vm_menu.h vm_utility.h vm_utility.c Makefile readme.txt
