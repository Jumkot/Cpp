CXX = g++
CXXFLAGS = -Wall -MMD -Wextra -Werror -std=c++20

APP = mines

all: $(APP)

$(APP): Board.o mines.o
	$(CXX) -o $(APP) Board.o mines.o
	rm -f *.[oad]

Board.o: Board.cpp
	$(CXX) $(CXXFLAGS) -c Board.cpp -o Board.o

mines.o: mines.cpp
	$(CXX) $(CXXFLAGS) -c mines.cpp -o mines.o

.PHONY: all