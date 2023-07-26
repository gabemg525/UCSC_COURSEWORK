CXX = g++
CXXFLAGS = -Wall

OBJECTS = LinkedList.o bard.o

bard: $(OBJECTS)
	$(CXX) -g $(CXXFLAGS) -o bard LinkedList.o bard.o

LinkedList.o: LinkedList.cpp LinkedList.h
	$(CXX) -g $(CXXFLAGS) -c LinkedList.cpp

bard.o: LinkedList.cpp LinkedList.h bard.cpp
	$(CXX) -g $(CXXFLAGS) -c bard.cpp

clean: 
	rm -f *.o
	rm bard