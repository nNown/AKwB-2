#pragma once 

#include <iostream>
#include <map>
#include <vector>

class Graph {
    private: 
        std::map<int, std::vector<int>> _vertices;
    public:
        std::map<int, std::vector<int>>& Vertices();

        void AddEdge(const int& i, const int& j);
        bool HasEdge(const int& i, const int& j);

        void AddVertex(const int& i);
        bool HasVertex(const int& i);

        Graph();
        Graph(const Graph& graphCopy);
        ~Graph();
};