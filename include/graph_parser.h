#pragma once

#include <fstream>
#include <filesystem>
#include <iostream>
#include <regex>
#include <stdexcept>
#include <vector>
#include <graph.h>

class GraphParser {
    private:
        static GraphParser* _parserInstance;
        GraphParser();
        
        
    public:
        Graph LoadGraph(const std::string& path);
        void SaveGraph(Graph& graph, const std::string& path);
        static GraphParser* GraphParserInstance();
        ~GraphParser();
};