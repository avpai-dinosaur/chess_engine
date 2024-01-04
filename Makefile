CXX ?= g++
CXXFLAGS ?= -Wall -Werror -pedantic -g --std=c++17 -Wno-sign-compare -Wno-comment

# Run regression test
test: main.exe
	./main.exe < main_test.in > main_test.out
	diff main_test.out main_test.out.correct
	echo PASS
	
# Compile the main executable
engine.exe: main.cpp Engine.cpp Board.cpp
	$(CXX) $(CXXFLAGS) main.cpp Engine.cpp Board.cpp -o engine.exe

# Remove automatically generated files
clean :
	rm -rvf *.exe *~ *.out *.dSYM *.stackdump
