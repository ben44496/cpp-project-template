#include "include/pagerank.h"
#include "parser_header.h"
#include <fstream>
#include <iostream>
#include <unordered_set>
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::unordered_set;
using std::ifstream;
using std::ofstream;
using Parser::CSVParser;
using Parser::Edge;

int main(){
    string filename = "nodes.txt";
    string output_filename = "pagerank.txt";

    // Open file and read into vector of IDs
    ifstream file;
    file.open(filename);

    if (!file.is_open()) {
        throw "Invalid file";
    }

    unordered_set<int> nodes;
    string node_string;
    while(getline(file, node_string)) {
        nodes.insert(std::stoi(node_string));
    }

    size_t size = nodes.size();

    std::cout << nodes.size() << " nodes processed for PageRank" << std::endl;

    // Parse railroad data
    string nodes_file = "../data/nodes.csv";
    string edges_file = "../data/edges.csv";
    CSVParser csvp(nodes_file, edges_file);

    csvp.parse();
    vector<Edge*> edges = csvp.GetEdges();

    std::cout << "Parsing complete" << std::endl;

    // Construct adjacency matrix
    vector<vector<float>> weights(size, vector<float>(size, 0));
    map<int, int> column_names;
    int row = 0;
    for (int n : nodes) {
        column_names[n] = row;
        ++row;
    }

    // Populate adjacency matrix
    for (Edge*& edge : edges) {
        if (column_names.find(edge->fromNode()) != column_names.end() 
            && column_names.find(edge->toNode()) != column_names.end()) {
            weights[column_names[edge->toNode()]][column_names[edge->fromNode()]] = 1;
        }
    }

    // Calculate the PageRank solution
    std::cout << "Starting PageRank" << std::endl;
    PageRank pr(weights, column_names);
    map<int, float> result = pr.solve();
    std::pair<int, float> best = pr.best_rank();
    std::cout << "PageRank complete" << std::endl;

    // Output solution
    std::cout << "Top station ID: " << best.first << std::endl;

    // Output full solution to a file
    ofstream output(output_filename);
    for (auto p : result) {
        output << p.first << " " << p.second << std::endl;
    }
    std::cout << "Full solution printed to " << output_filename << std::endl;

    return 0;
}