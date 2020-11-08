#include <graph.h>
#include <graph_parser.h>
#include <iostream>

int main(int argc, char* argv[]) {
    GraphParser* parser = GraphParser::GraphParserInstance();
    // Graph* test = parser->LoadGraph(std::string(argv[1]));
    // for(auto& vertex : test->Vertices()) {
    //     for(auto& edge : vertex.Edges()) {
    //         std::cout << edge << " ";
    //     }
    //     std::cout << std::endl;
    // }

    // Graph example(3);
    // example.AddEdge(0, 1);
    // example.AddEdge(0, 2);
    // example.AddEdge(1, 0);
    // example.AddEdge(2, 1);
    // example.AddEdge(2, 0);
    // parser->SaveGraph(example, "./tests");
    
    return 0;
}