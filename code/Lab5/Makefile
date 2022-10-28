TARGET_EXEC = sched

CC := g++ -g -lpthread

CFLAGS := -Wall -c $(DEBUG) -std=c++11 -lpthread

MAKE_FILE_PATH := $(PWD)
APP_PATH := $()

OBJS := sched.cpp queue.cpp

.PHONY: all clean

all: $(TARGET_EXEC)
$(TARGET_EXEC): $(OBJS)
	@echo "Input file:"
	@cat input.txt
	@$(CXX) -o $(LDFLAGS)  $@ $^
	@echo "Results"
	@cat input.txt | ./$(TARGET_EXEC)

.cpp.o:
	$(CC) -c $(CFLAGS) $(INCDR) $<

clean:
	rm -f $(TARGET_EXEC) *.o
