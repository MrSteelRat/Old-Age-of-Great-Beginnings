# Compiler to use
CC = gcc

# Compiler flags
CFLAGS = -Wall -g

# Utillity to creates archives
AR = ar

# ar flags
ARFLAGS = rcs

# Source files for LRU cache
LRU_SRCS = linux-utils/rbtree.c cache_lru.c

# Source file for tests
TEST_SRCS = tests.c

# Object files for LRU cache library
LRU_OBJS = $(LRU_SRCS:.c=.o)

# Object files for tests
TEST_OBJS = $(TEST_SRCS:.c=.o)

LRU_LIB = liblru.a

.PHONY: all clean tests

all: tests

# First target: LRU cache library
$(LRU_LIB): $(LRU_OBJS)
	$(AR) $(ARFLAGS) $(LRU_LIB) $(LRU_OBJS)

# Second target: tests executable
tests: $(LRU_LIB) $(TEST_OBJS)
	$(CC) $(CFLAGS) -o tests $(TEST_OBJS) -L. -llru

# Rule to build object files from source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(LIBRARY) tests $(TEST_OBJS) $(LRU_OBJS) $(LRU_LIB)