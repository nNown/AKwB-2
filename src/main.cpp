#include <cstdlib>
#include <chrono>
#include <graph.h>
#include <graph_parser.h>
#include <graph_generator.h>
#include <iostream>
#include <fstream>
#include <time.h>

int main(int argc, char* argv[]) {
    srand(time(NULL));
    GraphParser* parser = GraphParser::GraphParserInstance();
    GraphGenerator* generator = GraphGenerator::GraphGeneratorInstance();
    for(int i = 1; i < argc; i++) {
        Graph loadedGraph = parser->LoadGraph(argv[i]);
        if(generator->CheckIfGraphIsAdjoint(loadedGraph)) {
            bool isLinear = generator->CheckIfAdjointGraphIsLinear(loadedGraph);
            Graph transformed = generator->TransformAdjointGraphToItsOrigin(loadedGraph);
            parser->SaveGraph(transformed, "./", "transformed");
            std::cout << "Loaded graph is adjoint and " << (isLinear ? "is linear" : "is not linear") << " transformed graph was succesfully saved to file" << std::endl;
            continue;
        }
        std::cout << "Loaded graph is not adjoint" << std::endl;
    }
    return 0;
}