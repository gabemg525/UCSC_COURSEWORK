CXX = gcc
CXXFLAGS = -Wall -std=c11 -pthread


all: myserver myclient

OBJECTS = myserver.o myclient.o
myserver: $(OBJECTS)
	$(CXX) -g $(CXXFLAGS) -o bin/myserver myserver.o
    
myserver.o: src/myserver.c src/myclientserver.h
	$(CXX) -g $(CXXFLAGS) -c src/myserver.c

myclient: $(OBJECTS)
	$(CXX) -g $(CXXFLAGS) -o bin/myclient myclient.o
    
myclient.o: src/myclient.c src/myclientserver.h
	$(CXX) -g $(CXXFLAGS) -c src/myclient.c


clean: 
	rm -f *.o
	rm bin/myserver 
	rm bin/myclient


