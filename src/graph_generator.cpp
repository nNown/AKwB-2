#include <graph_generator.h>

GraphGenerator* GraphGenerator::_generatorInstance = nullptr;
GraphGenerator::GraphGenerator() {}

Graph GraphGenerator::GenerateRandomDirectedGraph(const std::size_t& size, const float& density, const bool& isSimple) {
    if(density > 1 || density < 0 || size <= 0) {
        throw std::logic_error("Density must be number between 0 and 1 and size must be bigger than 0");
    }

    std::size_t numberOfEdges = density * size * (size - 1) / 2.0;
    std::vector<int> randomizedConnections = std::vector<int>(2 * numberOfEdges);
    std::for_each(randomizedConnections.begin(), randomizedConnections.end(), [size](int& element) mutable { element = rand() % size; });
    [&randomizedConnections, this]() mutable {
        for(int i = randomizedConnections.size() - 1; i > 0; i--) {
            int j = rand() % i + 1;
            this->Swap<int>(&randomizedConnections[i], &randomizedConnections[j]);
        }
    }();

    Graph randomGraph = Graph();
    for(std::size_t i = 0; i < size; i++) {
        randomGraph.AddVertex(i);
    }

    if(!isSimple) {
        for(std::size_t i = 0; i < randomizedConnections.size(); i += 2) {
            randomGraph.AddEdge(randomizedConnections[i], randomizedConnections[i + 1]);
        }
    } else {
        for(std::size_t i = 0; i < randomizedConnections.size(); i += 2) {
            while(randomGraph.HasEdge(randomizedConnections[i], randomizedConnections[i + 1])) {
                randomizedConnections[i] = rand() % (size - 1);
                randomizedConnections[i + 1] = rand() % (size - 1);
            }
            randomGraph.AddEdge(randomizedConnections[i], randomizedConnections[i + 1]);
        }
    }

    return randomGraph;
}

Graph GraphGenerator::TransformToAdjointGraph(Graph& graph) {
    std::vector<std::tuple<int, int>> adjointGraphVertices = std::vector<std::tuple<int, int>>();
    for(auto i = graph.Vertices().begin(); i != graph.Vertices().end(); ++i) {
        for(std::size_t j = 0; j < graph.Vertices()[i->first].size(); j++) {
            adjointGraphVertices.push_back(std::make_tuple(i->first, graph.Vertices()[i->first][j]));
        }
    }

    Graph adjointGraph = Graph();
    for(std::size_t i = 0; i < adjointGraphVertices.size(); i++) {
        adjointGraph.AddVertex(i);
    }

    for(std::size_t i = 0; i < adjointGraphVertices.size(); i++) {
        auto& [ tail, head ] = adjointGraphVertices[i];
        for(std::size_t j = 0; j < adjointGraphVertices.size(); j++) {
            auto& [ comparedTail, comparedHead ] = adjointGraphVertices[j];
            if (head == comparedTail) {
                adjointGraph.AddEdge(i, j);
            }
        }
    }

    return adjointGraph;
}

Graph GraphGenerator::TransformAdjointGraphToItsOrigin(Graph& graph) {
    std::map<int, std::array<int, 2>> originGraphEdges = std::map<int, std::array<int, 2>>();
    int currentEdge = 0;
    for(auto i = graph.Vertices().begin(); i != graph.Vertices().end(); ++i) {
        originGraphEdges.insert({i->first, {currentEdge++, currentEdge++}});
    }

    for(auto i = graph.Vertices().begin(); i != graph.Vertices().end(); ++i) {
        for(auto& [ associatedVertex, edge ] : originGraphEdges) {
            if(graph.HasEdge(i->first, associatedVertex)) {
                int changedIndex = edge[0];
                edge[0] = originGraphEdges[i->first][1];
                for(auto& [ vertex, changedEdge ] : originGraphEdges) {
                    if(changedEdge[0] == changedIndex) changedEdge[0] = originGraphEdges[i->first][1];
                    if(changedEdge[1] == changedIndex) changedEdge[1] = originGraphEdges[i->first][1];
                }
            }
        }
    }

    Graph origin = Graph();
    for(auto& [ associatedVertex, edge ] : originGraphEdges) {
        if(!origin.HasVertex(edge[0])) origin.AddVertex(edge[0]);
        if(!origin.HasVertex(edge[1])) origin.AddVertex(edge[1]);

        origin.AddEdge(edge[0], edge[1]);
    }

    return origin;
}

bool GraphGenerator::CheckIfGraphIsAdjoint(Graph& graph) {
    for(auto& [ vertex, edgeList ] : graph.Vertices()) {
        for(auto& [ comparedVertex, comparedEdgeList ] : graph.Vertices()) {
            if(edgeList != comparedEdgeList) {
                for(auto& element : edgeList) {
                    for(auto& comparedElement : comparedEdgeList) {
                        if(element == comparedElement) {
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}

bool GraphGenerator::CheckIfAdjointGraphIsLinear(Graph& adjointGraph) {
    for(auto i = adjointGraph.Vertices().begin(); i != adjointGraph.Vertices().end(); ++i) {
        for(auto j = adjointGraph.Vertices().begin(); j != adjointGraph.Vertices().end(); ++j) {
            if(adjointGraph.Vertices()[i->first] == adjointGraph.Vertices()[j->first]) {
                for(auto& [ vertex, edgeList ] : adjointGraph.Vertices()) {
                    int commonPredecessor = 0;
                    for(auto& element : edgeList) {
                        if(element == i->first || element == j->first) ++commonPredecessor;
                    }
                    if(commonPredecessor >= 2) return false;
                }
            }
        }
    }
    return true;
}

bool GraphGenerator::CheckIfGraphIsSimple(Graph& graph) {
    for(auto& [ associatedVertex, edgeList ] : graph.Vertices()) {
        int duplicates = 0;
        for(auto& element : edgeList) {
            for(auto& comparedElement : edgeList) {
                if(element == comparedElement) ++duplicates;
            }
            if(duplicates > 1) return false;
            duplicates = 0;
        }
    }
    return true;
}

GraphGenerator* GraphGenerator::GraphGeneratorInstance() {
    if(_generatorInstance == nullptr) {
        _generatorInstance = new GraphGenerator();
    }

    return _generatorInstance;
}

GraphGenerator::~GraphGenerator() {}