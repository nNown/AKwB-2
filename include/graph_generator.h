#pragma once

#include <cstdlib>
#include <graph.h>
#include <stdexcept>
#include <vector>

class GraphGenerator {
    private:
        static GraphGenerator* _generatorInstance;
        GraphGenerator();


    public:
        Graph GenerateRandomDirectedGraph(const std::size_t& size, const float& density);
        static GraphGenerator* GraphGeneratorInstance();
        ~GraphGenerator();
};