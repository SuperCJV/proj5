CXX = g++
CXXFLAGS = -std=c++11 -g -Wall -Wextra

TASK5_OBJS = proj5.o

all: test_stack.x in2post.x

proj5.x: $(TASK5_OBJS)
	$(CXX) $(CXXFLAGS) -o proj5.x $(TASK5_OBJS)

proj5.o: proj5.cpp hashtable.h hashtable.hpp
	$(CXX) $(CXXFLAGS) -c proj5.cpp

clean:
	rm -f *.o proj5.x

.PHONY: all clean