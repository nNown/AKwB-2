#include <cstdlib>
#include <graph.h>
#include <graph_parser.h>
#include <graph_generator.h>
#include <iostream>
#include <time.h>

int main(int argc, char* argv[]) {
    srand(time(NULL));
    GraphParser* parser = GraphParser::GraphParserInstance();
    GraphGenerator* generator = GraphGenerator::GraphGeneratorInstance();

    Graph example = generator->GenerateRandomDirectedGraph(10, 0.85, true);
    std::cout << "Example graph " << (generator->CheckIfGraphIsAdjoint(example) ? "true" : "false") << std::endl;
    std::cout << "Graph Size: " << example.Vertices().size() << std::endl;
    parser->SaveGraph(example, "./tests");

    example = generator->TransformToAdjointGraph(example);
    std::cout << "Adjoint " << (generator->CheckIfGraphIsAdjoint(example) ? "true" : "false") << std::endl;
    std::cout << "Adjoint linear " << (generator->CheckIfAdjointGraphIsLinear(example) ? "true" : "false") << std::endl;
    std::cout << "Graph Size: " << example.Vertices().size() << std::endl;
    parser->SaveGraph(example, "./tests");

    example = generator->TransformAdjointGraphToItsOrigin(example);
    std::cout << "Is transfomed to origin adjoint? " << (generator->CheckIfGraphIsAdjoint(example) ? "true" : "false") << std::endl;
    std::cout << "Graph Size: " << example.Vertices().size() << std::endl;
    parser->SaveGraph(example, "./tests");

    return 0;
}