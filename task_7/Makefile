CXX = g++
CXXFLAGS = -Wall -std=c++20 -g
LDFLAGS = -lgtest -lgtest_main -pthread

APP = string_test

all: $(APP)

$(APP): String.o String.test.o 
	$(CXX) -o $(APP) String.o String.test.o $(LDFLAGS)
	rm -f *.[oad]

String.test.o: String.test.cpp
	$(CXX) $(CXXFLAGS) -c String.test.cpp -o String.test.o $(LDFLAGS)

String.o: String.cpp
	$(CXX) $(CXXFLAGS) -c String.cpp -o String.o $(LDFLAGS)

.PHONY: all