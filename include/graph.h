#pragma once 

#include <iostream>
#include <vector>

class EdgeList {
    private:
        size_t _size;
        std::vector<int> _edges;
    
    public: 
        const size_t& Size() const;
        void Size(const size_t& size);

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

        Graph(const size_t& size);
        ~Graph();
};