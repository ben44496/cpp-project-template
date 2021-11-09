#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "parser_header.h"
#include <string>
#include "include/BFS.h"

using std::string;
using Parser::CSVParser;
using Parser::Edge;
using Parser::Node;

int main() {
    // Instantiate files and CSVParser
    string nodes_file = "../data/nodes.csv";
    string edges_file = "../data/edges.csv";
    CSVParser csvp(nodes_file, edges_file);

    // Parse the nodes and edges into the instance variables
    csvp.parse();

    // Print out number of Nodes and Edges
    std::vector<Node*> nodes = csvp.GetNodes();
    std::vector<Edge*> edges = csvp.GetEdges();      
    std::cout << nodes.size() << std::endl;
    std::cout << edges.size() << std::endl;

    BFS bfs(nodes[0]);

    int i = 0;
    for (auto it = bfs.begin(); it != bfs.end(); ++it) {
        std::cout << (*it)->getId() << " ID" << std::endl;        
        std::cout << (*it)->getOutbound().size() << " next outbound ID" << std::endl; 
        i++;
    }
    std::cout << i << " connected nodes" << std::endl;

    return 0;
}