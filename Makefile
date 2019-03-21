EXECUTABLE = image
OBJS = process.o cell.o image.o
CXX = g++
CXXFLAGS = -std=c++1y -static-libstdc++ -c -g -O0 -Wall -Wextra -pedantic
LD = g++
LDFLAGS = -std=c++1y -static-libstdc++ -lpng

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXECUTABLE)

process.o: process.cpp cell.h image.h
	$(CXX) $(CXXFLAGS) process.cpp

cell.o: cell.cpp cell.h
	$(CXX) $(CXXFLAGS) cell.cpp

image.o: image.cpp image.h cell.h
	$(CXX) $(CXXFLAGS) image.cpp

clean:
	-rm -f *.o $(EXECUTABLE)
