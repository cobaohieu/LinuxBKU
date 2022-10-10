TARGET_EXEC := exe_2_2

CXX := g++
CFLAGS := -std=c++11

# Find all the C and C++ files we want to compile
SRCS := $(wildcard *.cpp)

# String substitution for every C/C++ file.
OBJS := $(patsubst %.cpp,%.o,$(SRCS))

.PHONY: all clean

all: $(TARGET_EXEC)
$(TARGET_EXEC): $(OBJS)
	$(CXX) -o $@ $^
%.o: %.cpp
	$(CXX) $(CFLAGS) -c $<
	
clean:
	rm -rf $(TARGET_EXEC) *.o
