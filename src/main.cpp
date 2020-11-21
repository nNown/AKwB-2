#include <cstdlib>
#include <graph.h>
#include <graph_parser.h>
#include <graph_generator.h>
#include <iostream>
#include <time.h>

int main(int argc, char* argv[]) {
    GraphParser* parser = GraphParser::GraphParserInstance();
    srand(time(NULL));
    GraphGenerator* generator = GraphGenerator::GraphGeneratorInstance();

    for(int i = 1; i < argc; i++) {
        Graph test = parser->LoadGraph(std::string(argv[i]));
        for(auto& vertex : test.Vertices()) {
            for(auto& edge : vertex.Edges()) {
                std::cout << edge << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    return 0;
}