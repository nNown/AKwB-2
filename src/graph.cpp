#include <graph.h>

const size_t& EdgeList::Size() const { return this->_size; }
void EdgeList::Size(const size_t& size) { this->_size = size; }

std::vector<int>& EdgeList::Edges() { return this->_edges; }

EdgeList::EdgeList() 
    : _size(0), _edges(std::vector<int>(0)) {}

EdgeList::~EdgeList() {}

std::vector<EdgeList>& Graph::Vertices() { return this->_vertices; }

void Graph::AddEdge(const int& i, const int& j) {
    this->_vertices[i].Edges().push_back(j);
    this->_vertices[i].Size(this->_vertices[i].Size() + 1);
}

bool Graph::HasEdge(const int& i, const int& j) { 
    for(size_t k = 0; k < this->_vertices[i].Edges().size(); k++) {
        if(this->_vertices[i].Edges()[k] == j) return true;
    }
    return false;
}

void Graph::AddVertex() {
    this->_vertices.push_back(EdgeList());
}

Graph::Graph(const size_t& size) 
    : _vertices(std::vector<EdgeList>(size, EdgeList())) {}
Graph::~Graph() {}