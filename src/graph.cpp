#include <graph.h>

std::map<int, std::vector<int>>& Graph::Vertices() { return this->_vertices; }

void Graph::AddEdge(const int& i, const int& j) {
    this->_vertices[i].push_back(j);
}

bool Graph::HasEdge(const int& i, const int& j) { 
    for(size_t k = 0; k < this->_vertices[i].size(); k++) {
        if(this->_vertices[i][k] == j) return true;
    }
    return false;
}

void Graph::AddVertex(const int& i) {
    this->_vertices.insert({i, std::vector<int>()});
}

bool Graph::HasVertex(const int& i) {
    return this->_vertices.find(i) != this->_vertices.end() ? true : false;
}

Graph::Graph() 
    : _vertices(std::map<int, std::vector<int>>()) {}

Graph::Graph(const Graph& graphCopy) 
    : _vertices(graphCopy._vertices) {}

Graph::~Graph() {}