#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <map>
#include "node.h"
#include "edge.h"

namespace Parser {
class CSVParser {
    public:
        CSVParser(const std::string& nodes_file, const std::string& edges_file);
        CSVParser(const CSVParser& other);
        CSVParser& operator=(const CSVParser& other);
        ~CSVParser();

        void parse();
        std::string print();
        std::vector<Node*> GetNodes();
        std::vector<Edge*> GetEdges();
        std::vector<std::vector<double>> GetAdjacencyMatrixDirected();
        std::vector<std::vector<double>> GetAdjacencyMatrixUndirected();
        std::map<int, int> GetAdjacencyIndexMap();
        int rows();
    private:
        std::string nodes_file_;
        std::string edges_file_;
        std::vector<Node*> nodes_;
        std::map<int, Node*> nodes_map_;
        std::vector<Edge*> edges_;
        
        std::vector<std::vector<double>> adjacency_matrix_directed_;
        std::vector<std::vector<double>> adjacency_matrix_undirected_;
        std::map<int, int> adjacency_index_map_;

        std::vector<Node*> parseNodes(const std::string& nodes_file);
        std::vector<Edge*> parseEdges(const std::string& edges_file);
};

}