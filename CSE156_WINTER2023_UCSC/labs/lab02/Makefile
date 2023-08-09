CXX = g++
CXXFLAGS = -Wall -std=c++11 

all: myserver myclient

OBJECTS = myserver.o myclient.o
myserver: $(OBJECTS)
	$(CXX) -g $(CXXFLAGS) -o bin/myserver myserver.o
    
myserver.o: src/myserver.c
	$(CXX) -g $(CXXFLAGS) -c src/myserver.c

myclient: $(OBJECTS)
	$(CXX) -g $(CXXFLAGS) -o bin/myclient myclient.o
    
myclient.o: src/myclient.c
	$(CXX) -g $(CXXFLAGS) -c src/myclient.c


clean: 
	rm -f *.o
	rm bin/myserver 
	rm bin/myclient
