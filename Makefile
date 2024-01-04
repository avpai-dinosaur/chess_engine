CXX ?= g++
CXXFLAGS ?= -Wall -Werror -pedantic -g --std=c++17 -Wno-sign-compare -Wno-comment

# Run regression test
test: engine.exe
	./engine.exe < tests/kingsTouch > tests/kingsTouch.out
	diff tests/kingsTouch.out tests/kingsTouch.correct
	echo PASS
	
# Compile the main executable
engine.exe: main.cpp Engine.cpp Board.cpp
	$(CXX) $(CXXFLAGS) main.cpp Engine.cpp Board.cpp -o engine.exe

# Remove automatically generated files
clean :
	rm -rvf *.exe *~ *.out *.dSYM *.stackdump
