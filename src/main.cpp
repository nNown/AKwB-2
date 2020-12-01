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

    std::ofstream resultsFile = std::ofstream("results.txt", std::ios::out);

    int graphSizes[] = { 10, 15, 20, 25, 30, 35, 40, 45, 50 };
    float graphDensities[] = { 0.15, 0.3, 0.45, 0.6, 0.85, 0.9 };
    std::function<Graph(const std::size_t&, const float&)> graphTypes[] = { 
        [generator](const std::size_t& size, const float& density){ return generator->GenerateRandomDirectedGraph(size, density, false); }, 
        [generator](const std::size_t& size, const float& density){ return generator->GenerateRandomDirectedGraph(size, density, true); }, 
        [generator](const std::size_t& size, const float& density){ 
            Graph randomGraph = generator->GenerateRandomDirectedGraph(size, density, false);
            return generator->TransformToAdjointGraph(randomGraph);
        },
        [generator](const std::size_t& size, const float& density){ 
            Graph randomGraph = generator->GenerateRandomDirectedGraph(size, density, true);
            return generator->TransformToAdjointGraph(randomGraph);
        }
    };

    for(auto& density : graphDensities) {
        for(auto& size : graphSizes) {
            for(auto& graph : graphTypes) {
                Graph testedGraph = graph(size, density);
                std::stringstream graphName;

                bool isSimple = generator->CheckIfGraphIsSimple(testedGraph);

                auto t1 = std::chrono::high_resolution_clock::now();
                bool isAdjoint = generator->CheckIfGraphIsAdjoint(testedGraph);
                auto t2 = std::chrono::high_resolution_clock::now();

                graphName << "transformed:false" << "_" << "multi:" << (isSimple ? "false" : "true") << "_" << "adjoint:false" << "_" << "size:" << size << "_" << "density:" << density;
                
                double defaultGraphAdjointTestTime = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
                resultsFile << "Graph: " << "size: " << size << " " << "density: " << density << " " << "multi: " << (isSimple ? "false" : "true") << " " << "adjoint: " << (isAdjoint ? "true" : "false") << ":" << defaultGraphAdjointTestTime << " ";
                
                if(isAdjoint) {
                    graphName.str(std::string());
                    auto t3 = std::chrono::high_resolution_clock::now();
                    bool isLinear = generator->CheckIfAdjointGraphIsLinear(testedGraph);
                    auto t4 = std::chrono::high_resolution_clock::now();

                    graphName << "transformed:false" << "_" << "multi:" << (isSimple ? "false" : "true") << "_" << "adjoint:true" << "_" << "linear:" << (isLinear ? "true" : "false") << "_" << "size:" << size << "_" << "density:" << density;
                    parser->SaveGraph(testedGraph, "./tests", graphName.str());
                    graphName.str(std::string());

                    Graph transformedGraph = Graph();

                    auto t5 = std::chrono::high_resolution_clock::now();
                    transformedGraph = generator->TransformAdjointGraphToItsOrigin(testedGraph);
                    auto t6 = std::chrono::high_resolution_clock::now();

                    bool isTransformedSimple = generator->CheckIfGraphIsSimple(testedGraph);

                    auto t7 = std::chrono::high_resolution_clock::now();
                    bool isTransformedAdjoint = generator->CheckIfGraphIsAdjoint(testedGraph);
                    auto t8 = std::chrono::high_resolution_clock::now();

                    auto t9 = std::chrono::high_resolution_clock::now();
                    bool isTransformedLinear = isAdjoint ? generator->CheckIfAdjointGraphIsLinear(testedGraph) : false;
                    auto t10 = std::chrono::high_resolution_clock::now();

                    graphName << "transformed:true" << "_" << "multi:" << (isTransformedSimple ? "true" : "false") << "_" << "adjoint:" << (isTransformedAdjoint ? "true" : "false") << "_" << "linear:" << (isTransformedLinear ? "true" : "false") << "_" << "size:" << transformedGraph.Vertices().size();
                    parser->SaveGraph(transformedGraph, "./tests", graphName.str());

                    double defaultGraphLinearTestTime = std::chrono::duration_cast<std::chrono::milliseconds>(t4 - t3).count();
                    double graphTransformationTIme = std::chrono::duration_cast<std::chrono::milliseconds>(t6 - t5).count();
                    double transformedGraphAdjointTestTime = std::chrono::duration_cast<std::chrono::milliseconds>(t8 - t7).count();
                    double transformedGraphLinearTestTime = std::chrono::duration_cast<std::chrono::milliseconds>(t10 - t9).count();
                    resultsFile << "linear: " << (isLinear ? "true" : "false") << ":" << defaultGraphLinearTestTime << " " << "Transformed graph:" << graphTransformationTIme << " " << "size: " << transformedGraph.Vertices().size() << " "<< "multi: " << (isTransformedSimple ? "true" : "false") << " " << "adjoint:" << (isTransformedAdjoint ? "true" : "false") << ":" << transformedGraphAdjointTestTime << " " << "linear:" << (isTransformedLinear ? "true" : "false") << ":" << transformedGraphLinearTestTime << std::endl;
                    continue;
                }

                parser->SaveGraph(testedGraph, "./tests", graphName.str());
                resultsFile << std::endl;
            }
        }
    }

    resultsFile.close();
    return 0;
}