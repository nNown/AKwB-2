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
        Graph example = parser->LoadGraph(argv[i]);
        if(generator->CheckIfGraphIsAdjoint(example)) {
            bool isLinear = generator->CheckIfAdjointGraphIsLinear(example);
            Graph transformed = generator->TransformAdjointGraphToItsOrigin(example);
            parser->SaveGraph(transformed, "./output", "transfomred");
            std::cout << "Loaded graph is adjoint and " << (isLinear ? "is linear" : "is not linear") << " transformed graph was succesfully saved to file" << std::endl;
            continue;
        }
        std::cout << "Loaded graph is not adjoint" << std::endl;
    }

    // std::ofstream resultsFile = std::ofstream("results.txt", std::ios::out);

    // int graphSizes[] = { 10, 15, 20, 25, 30, 35, 40, 45, 50 };
    // float graphDensities[] = { 0.15, 0.3, 0.45, 0.6, 0.75, 0.9 };
    // std::function<Graph(const std::size_t&, const float&)> graphTypes[] = { 
    //     [generator](const std::size_t& size, const float& density){ return generator->GenerateRandomDirectedGraph(size, density, false); }, 
    //     [generator](const std::size_t& size, const float& density){ return generator->GenerateRandomDirectedGraph(size, density, true); }, 
    //     [generator](const std::size_t& size, const float& density){ 
    //         Graph randomGraph = generator->GenerateRandomDirectedGraph(size, density, false);
    //         return generator->TransformToAdjointGraph(randomGraph);
    //     },
    //     [generator](const std::size_t& size, const float& density){ 
    //         Graph randomGraph = generator->GenerateRandomDirectedGraph(size, density, true);
    //         return generator->TransformToAdjointGraph(randomGraph);
    //     }
    // };

    // for(auto& density : graphDensities) {
    //     for(auto& size : graphSizes) {
    //         for(auto& graph : graphTypes) {
    //             Graph testedGraph = graph(size, density);
    //             std::stringstream graphName;

    //             bool isSimple = generator->CheckIfGraphIsSimple(testedGraph);
    //             bool isAdjoint = generator->CheckIfGraphIsAdjoint(testedGraph);

    //             graphName << "transformed:false" << "_" << "multi:" << (isSimple ? "false" : "true") << "_" << "adjoint:false" << "_" << "size:" << testedGraph.Vertices().size() << "_" << "density:" << density;
    //             resultsFile << "Graph: " << "size: " << testedGraph.Vertices().size() << "\t" << "density: " << density << "\t" << "multi: " << (isSimple ? "false" : "true") << "\t" << "adjoint: " << (isAdjoint ? "true" : "false") << " ";
                
    //             if(isAdjoint) {
    //                 graphName.str(std::string());
    //                 bool isLinear = generator->CheckIfAdjointGraphIsLinear(testedGraph);

    //                 graphName << "transformed:false" << "_" << "multi:" << (isSimple ? "false" : "true") << "_" << "adjoint:true" << "_" << "linear:" << (isLinear ? "true" : "false") << "_" << "size:" << testedGraph.Vertices().size() << "_" << "density:" << density;
    //                 parser->SaveGraph(testedGraph, "./tests", graphName.str());
    //                 graphName.str(std::string());

    //                 Graph transformedGraph = Graph();

    //                 transformedGraph = generator->TransformAdjointGraphToItsOrigin(testedGraph);

    //                 bool isTransformedSimple = generator->CheckIfGraphIsSimple(transformedGraph);
    //                 bool isTransformedAdjoint = generator->CheckIfGraphIsAdjoint(transformedGraph);
    //                 bool isTransformedLinear = isTransformedAdjoint ? generator->CheckIfAdjointGraphIsLinear(transformedGraph) : false;

    //                 graphName << "transformed:true" << "_" << "multi:" << (isTransformedSimple ? "false" : "true") << "_" << "adjoint:" << (isTransformedAdjoint ? "true" : "false") << "_" << "linear:" << (isTransformedLinear ? "true" : "false") << "_" << "size:" << transformedGraph.Vertices().size();
    //                 parser->SaveGraph(transformedGraph, "./tests", graphName.str());

    //                 resultsFile << "linear: " << (isLinear ? "true" : "false") << "\t" << "Transformed graph" << "\t" << "size: " << transformedGraph.Vertices().size() << "\t"<< "multi: " << (isTransformedSimple ? "false" : "true") << "\t" << "adjoint:" << (isTransformedAdjoint ? "true" : "false") << "\t" << "linear:" << (isTransformedLinear ? "true" : "false") << std::endl;
    //                 continue;
    //             }

    //             parser->SaveGraph(testedGraph, "./tests", graphName.str());
    //             resultsFile << std::endl;
    //         }
    //     }
    // }

    // resultsFile.close();
    return 0;
}