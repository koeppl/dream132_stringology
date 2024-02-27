TARGET:=$(patsubst %.cpp,%.x,$(wildcard *.cpp))
all: $(TARGET)
CXX = g++
MYCXXFLAGS  = -ggdb -Wall -pedantic -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -std=gnu++11

%.x : %.cpp
	$(CXX) $(MYCXXFLAGS) $(CXXFLAGS) -o $@ $<

clean:
	$(RM) $(TARGET)
