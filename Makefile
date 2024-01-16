CXX ?= g++
CXXFLAGS ?= -Wall -Werror -pedantic -g --std=c++17 -Wno-sign-compare -Wno-comment
	
# Compile the main executable
engine.exe: main.cpp Engine.o Board.o
	$(CXX) $(CXXFLAGS) main.cpp Engine.o Board.o -o engine.exe

Engine.o: Engine.h Engine.cpp
	$(CXX) $(CXXFLAGS) Engine.cpp -c

Board.o: Board.h Board.cpp
	$(CXX) $(CXXFLAGS) Board.cpp -c

# Compile tests
test: tests-main.o Engine.o Board.o tests-engine.cpp tests-board.cpp
	$(CXX) $(CXXFLAGS) tests-main.o Engine.o Board.o tests-engine.cpp tests-board.cpp -o test && ./test

tests-main.o: tests-main.cpp
	$(CXX) $(CXXFLAGS) tests-main.cpp -c


# Remove automatically generated files
clean :
	rm -rvf *.exe *~ *.out *.dSYM *.stackdump *.o
