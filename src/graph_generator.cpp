#include <graph_generator.h>

GraphGenerator* GraphGenerator::_generatorInstance = nullptr;
GraphGenerator::GraphGenerator() {}

Graph GraphGenerator::GenerateRandomDirectedGraph(const std::size_t& size, const float& density) {
    if(density > 1 || density < 0 || size <= 0) {
        throw std::logic_error("Density must be number between 0 and 1 and size must be bigger than 0");
    }

    std::size_t edges = density * size * (size - 1) / 2.0;

    std::vector<int> randomizedChainOfVertices = std::vector<int>(2 * edges);
    for(std::size_t i = 0; i < 2 * edges; i++) randomizedChainOfVertices[i] = rand() % size;

    // Durstenfeld version of Fisher–Yates shuffle
    [&randomizedChainOfVertices]() mutable {
        for(int i = randomizedChainOfVertices.size() - 1; i > 0; i--) {
            int j = rand() % i + 1;
            int temp = randomizedChainOfVertices[i];
            randomizedChainOfVertices[i] = randomizedChainOfVertices[j];
            randomizedChainOfVertices[j] = temp;
        }
    }();

    Graph randomGraph = Graph(size);
    for(size_t i = 0; i < randomizedChainOfVertices.size(); i += 2) randomGraph.AddEdge(randomizedChainOfVertices[i], randomizedChainOfVertices[i + 1]);
    return randomGraph;
}

GraphGenerator* GraphGenerator::GraphGeneratorInstance() {
    if(_generatorInstance == nullptr) {
        _generatorInstance = new GraphGenerator();
    }

    return _generatorInstance;
}

GraphGenerator::~GraphGenerator() {}