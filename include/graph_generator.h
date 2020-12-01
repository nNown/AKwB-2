#pragma once

#include <algorithm>
#include <array>
#include <cstdlib>
#include <functional>
#include <graph.h>
#include <stdexcept>
#include <vector>

class GraphGenerator {
    private:
        static GraphGenerator* _generatorInstance;
        GraphGenerator();

        template<typename T>
        void Swap(T* firstItem, T* secondItem) {
            T* temp = firstItem;
            firstItem = secondItem;
            secondItem = temp;
        }

    public:
        Graph GenerateRandomDirectedGraph(const std::size_t& size, const float& density, const bool& isSimple);
        Graph TransformToAdjointGraph(Graph& graph);
        Graph TransformAdjointGraphToItsOrigin(Graph& graph);
        bool CheckIfGraphIsAdjoint(Graph& graph);
        bool CheckIfAdjointGraphIsLinear(Graph& adjointGraph);
        bool CheckIfGraphIsSimple(Graph& graph);
        static GraphGenerator* GraphGeneratorInstance();
        ~GraphGenerator();
};