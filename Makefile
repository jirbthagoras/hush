
# ==============================================================================
# PROJECT CONFIGURATION
# ==============================================================================

# Target executable name
TARGET   := hush

# Compiler and tool choices
CC       := gcc
RM       := rm -rf

# Compilation flags
# -Wall -Wextra: Enable all warnings for clean code
# -g           : Generate debugging information for GDB
# -O2          : Apply safe optimization pass
CFLAGS   := -Wall -Wextra -g -O2

# Linking flags and libraries (e.g., -lm for math)
LDFLAGS  := 
LDLIBS   := 

# ==============================================================================
# SOURCE AND OBJECT FILE DETECTION
# ==============================================================================

# Automatically scan all .c files in the directory
SRCS     := $(wildcard *.c)

# Generate a list of matching .o object files
OBJS     := $(SRCS:.c=.o)

# ==============================================================================
# BUILD RULES
# ==============================================================================

# Default target executed when running 'make' alone
.PHONY: all
all: $(TARGET)

# Link the object files together to create the executable
$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

# Compile individual source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean up build artifacts safely across UNIX/Linux platforms
.PHONY: clean
clean:
	$(RM) $(OBJS) $(TARGET)
