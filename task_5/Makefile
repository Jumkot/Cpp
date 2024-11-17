CXX = g++
CXXFLAGS = -Wall -MMD -Wextra -Werror -std=c++20

APP = normpath

all: $(APP)

$(APP): normpath.o main.o 
	$(CXX) -o $(APP) normpath.o main.o 
	rm -f *.[oad]

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

normpath.o: normpath.cpp
	$(CXX) $(CXXFLAGS) -c normpath.cpp -o normpath.o

.PHONY: all