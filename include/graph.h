#pragma once 

#include <iostream>
#include <vector>

class EdgeList {
    private:
        std::vector<int> _edges;
    
    public: 
        std::vector<int>& Edges();

        EdgeList();
        ~EdgeList();
};

class Graph {
    private: 
        std::vector<EdgeList> _vertices;    
    public:
        std::vector<EdgeList>& Vertices();

        void AddEdge(const int& i, const int& j);
        bool HasEdge(const int& i, const int& j);

        void AddVertex();

        Graph();
        Graph(const size_t& size);
        Graph(const Graph& graphCopy);
        ~Graph();
};