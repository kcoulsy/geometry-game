# Name of the executable. Change this when copying the template.
APP := app

# CXX is Make's conventional variable for the C++ compiler. The ?= keeps a
# compiler supplied on the command line, for example: make CXX=clang++.
CXX ?= g++

SFML_CFLAGS := $(shell pkg-config --cflags sfml-graphics)
SFML_LIBS := $(shell pkg-config --libs sfml-graphics)


# Compiler options: C++20, common warnings, debug symbols, and include paths.
# -MMD -MP also asks the compiler to write header dependency files (*.d).
CXXFLAGS := -std=c++20 -Wall -Wextra -Wpedantic -g -Iinclude $(SFML_CFLAGS) -MMD -MP
LDLIBS := $(SFML_LIBS)

# Directories used by this template. Source files live in src; generated files
# are kept in build so they do not clutter the project root.
SRC_DIR := src
BUILD_DIR := build

# Find every .cpp source file, including subdirectories, and preserve its path
# under build. New source files are included automatically on the next make.
SOURCES := $(shell find $(SRC_DIR) -type f -name '*.cpp')
OBJECTS := $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
DEPS := $(OBJECTS:.o=.d)

# The default goal. Typing plain `make` builds the executable.
.DEFAULT_GOAL := all

# .PHONY marks names that are commands, not files. Without it, a file named
# "clean" or "run" could accidentally stop its matching recipe from running.
.PHONY: all run clean

# Link all object files into the final program. The order-only prerequisite
# ensures build/ exists but does not force a relink merely because its timestamp
# changes.
all: $(BUILD_DIR)/$(APP)

$(BUILD_DIR)/$(APP): $(OBJECTS) | $(BUILD_DIR)
	$(CXX) $(OBJECTS) -o $@ $(LDLIBS)

# Compile each source file separately. $< is the first prerequisite (the .cpp
# file); $@ is the target (the .o file). This rule also works for future files.
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create the output directory only when it is missing.
$(BUILD_DIR):
	mkdir -p $@

# Build first, then execute the program. The leading @ hides this command line
# itself; the program's own output remains visible.
run: all
	@./$(BUILD_DIR)/$(APP)

# Remove only generated files. Source code and project files are untouched.
clean:
	rm -rf $(BUILD_DIR)

# Include compiler-generated header dependencies when they exist. The leading
# dash tells Make not to fail before the first build, when no .d files exist.
-include $(DEPS)
