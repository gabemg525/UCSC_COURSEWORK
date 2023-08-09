CXX = g++
CXXFLAGS = -Wall -std=c++11 

OBJECTS = myweb.o
myweb: $(OBJECTS)
	$(CXX) -g $(CXXFLAGS) -o bin/myweb myweb.o
    
myweb.o: src/myweb.c
	$(CXX) -g $(CXXFLAGS) -c src/myweb.c


clean: 
	rm -f *.o
	rm bin/myweb 