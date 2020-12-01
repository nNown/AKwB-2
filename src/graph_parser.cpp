#include<graph_parser.h>

GraphParser* GraphParser::_parserInstance = nullptr;
GraphParser::GraphParser() {}

Graph GraphParser::LoadGraph(const std::string& path) {
    Graph graphFromFile = Graph();

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
            if(graphFromFile.Vertices().find(sourceVertex) != graphFromFile.Vertices().end()) {
                throw std::logic_error("Graph already has this vertex");
            }
            graphFromFile.AddVertex(sourceVertex);
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

void GraphParser::SaveGraph(Graph& graph, const std::string& path, const std::string& name) {
    std::stringstream filename;
    filename << path << "/" << name << ".graph";

    int filesWithTakenName = 0;
    while(std::filesystem::exists(filename.str())) {
        ++filesWithTakenName;
        filename.str(std::string());
        filename << path << "/" << name << "_" << filesWithTakenName << ".graph";
    }
    std::ofstream graphFile = std::ofstream(filename.str(), std::ios::out);

    for(auto i = graph.Vertices().begin(); i != graph.Vertices().end(); ++i) {
        graphFile << i->first << ": { ";
        for(std::size_t j = 0; j < graph.Vertices()[i->first].size(); j++) {
            if(graph.Vertices()[i->first].size() - 1 == j) graphFile << graph.Vertices()[i->first][j] << " ";
            else graphFile << graph.Vertices()[i->first][j] << ", ";
        }
        graphFile << "}" << std::endl;
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