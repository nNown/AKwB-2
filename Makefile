CXX = g++
CPPFLAGS = -Wall -Wextra -Wno-unused-parameter -Iinclude/ -g -Og -std=c++17
LFLAGS = -lstdc++fs

all: main

main: src/main.cpp src/graph.cpp src/graph_parser.cpp src/graph_generator.cpp
	$(CXX) $(CPPFLAGS) -o $@ $^ $(LFLAGS)