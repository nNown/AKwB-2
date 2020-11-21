#include <graph.h>

std::vector<int>& EdgeList::Edges() { return this->_edges; }

EdgeList::EdgeList() 
    :_edges(std::vector<int>(0)) {}

EdgeList::~EdgeList() {}

std::vector<EdgeList>& Graph::Vertices() { return this->_vertices; }

void Graph::AddEdge(const int& i, const int& j) {
    this->_vertices[i].Edges().push_back(j);
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

Graph::Graph() 
    : _vertices(std::vector<EdgeList>(0, EdgeList())) {}

Graph::Graph(const Graph& graphCopy) 
    : _vertices(graphCopy._vertices) {}

Graph::Graph(const size_t& size) 
    : _vertices(std::vector<EdgeList>(size, EdgeList())) {}

Graph::~Graph() {}