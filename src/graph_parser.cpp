#include<graph_parser.h>

GraphParser* GraphParser::_parserInstance = nullptr;
GraphParser::GraphParser() {}

Graph GraphParser::LoadGraph(const std::string& path) {
    Graph graphFromFile = Graph(0);

    std::ifstream graphFile = std::ifstream(path, std::ios::in);
    if(!graphFile.is_open()) {
        throw std::runtime_error("Failed to open file");
    }

    std::string line;
    std::regex vertexPattern(R"(^[0-9]+)");
    std::regex edgeListPattern(R"(\{(\s*)[0-9, ]*(\s*)?\})");

    std::smatch sm;
    while(std::getline(graphFile, line)) {
        int sourceVertex;
        if(std::regex_search(line, sm, vertexPattern)) {
            sourceVertex = std::stoi(sm.str());
            if((size_t)sourceVertex != graphFromFile.Vertices().size()) {
                throw std::logic_error("Graph already has this vertex");
            }
            graphFromFile.AddVertex();
        } else {
            throw std::logic_error("Graph file contains line that doesn't start with vertex index");
        }

        if(std::regex_search(line, sm, edgeListPattern)) {
            std::string destinationVertices = sm.str().substr(1, sm.str().size() - 2);
            destinationVertices.erase(std::remove(destinationVertices.begin(), destinationVertices.end(), ' '), destinationVertices.end());
            
            if(destinationVertices.empty()) continue;
            
            std::stringstream edgeList(destinationVertices);
            while(edgeList.good()) {
                std::string destinationVertex;
                std::getline(edgeList, destinationVertex, ',');
                graphFromFile.AddEdge(sourceVertex, std::stoi(destinationVertex));
            }
        } else {
            throw std::logic_error("Graph file doesn't contain properly formatted edge list");
        }
    }

    graphFile.close();
    return graphFromFile;
}

void GraphParser::SaveGraph(Graph& graph, const std::string& path) {
    std::stringstream ss;
    ss << path << "/graph_s" << graph.Vertices().size() << ".graph";

    int filesWithTakenName = 0;
    while(std::filesystem::exists(ss.str())) {
        ++filesWithTakenName;
        ss.str(std::string());
        ss << path << "/graph_s" << graph.Vertices().size() << "_" << filesWithTakenName << ".graph";
    }
    std::ofstream graphFile = std::ofstream(ss.str(), std::ios::out);

    for(size_t i = 0; i < graph.Vertices().size(); i++) {
        graphFile << i << ": { ";
        for(size_t j = 0; j < graph.Vertices()[i].Edges().size(); j++) {
            if(j == graph.Vertices()[i].Edges().size() - 1) graphFile << graph.Vertices()[i].Edges()[j] << " ";
            else graphFile << graph.Vertices()[i].Edges()[j] << ", ";
        }
        graphFile << "}\n";
    }

    graphFile.close();
}

GraphParser* GraphParser::GraphParserInstance() {
    if(_parserInstance == nullptr) {
        _parserInstance = new GraphParser();
    }

    return _parserInstance;
}

GraphParser::~GraphParser() {}