#include<graph_parser.h>

GraphParser* GraphParser::_parserInstance = nullptr;
GraphParser::GraphParser() {}

Graph* GraphParser::LoadGraph(const std::string& path) {
    Graph* graphFromFile = new Graph(0);

    std::ifstream graphFile = std::ifstream(path, std::ios::in);
    if(!graphFile.is_open()) {
        std::cerr << "Failed to open file" << std::endl;
        return nullptr;
    }

    std::string line;
    std::regex vertexPattern(R"(^[0-9]+)");
    std::regex edgeListPattern(R"(\{(\s*)[0-9, ]*(\s*)?\})");

    std::smatch sm;
    while(std::getline(graphFile, line)) {
        int sourceVertex;
        if(std::regex_search(line, sm, vertexPattern)) {
            sourceVertex = std::stoi(sm.str());
            if((size_t)sourceVertex != graphFromFile->Vertices().size()) {
                std::cerr << "Graph already has this vertex" << std::endl;
                return nullptr;
            }
            graphFromFile->AddVertex();
        } else {
            std::cerr << "Graph file contains line that doesn't start with vertex index" << std::endl;
            return nullptr;
        }

        if(std::regex_search(line, sm, edgeListPattern)) {
            std::string destinationVertices = sm.str().substr(1, sm.str().size() - 2);
            destinationVertices.erase(std::remove(destinationVertices.begin(), destinationVertices.end(), ' '), destinationVertices.end());
            
            std::stringstream edgeList(destinationVertices);
            while(edgeList.good()) {
                std::string destinationVertex;
                std::getline(edgeList, destinationVertex, ',');
                graphFromFile->AddEdge(sourceVertex, std::stoi(destinationVertex));
            }
        } else {
            std::cerr << "Graph file doesn't contain properly formatted edge list" << std::endl;
            return nullptr;
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