#include "include/parser_header.h"

using Parser::CSVParser;
using Parser::Node;
using Parser::Edge;
using std::string;

int main() {
    string nodes_file = "../data/nodes.csv";
    string edges_file = "../data/edges.csv";
    CSVParser csvp(nodes_file, edges_file);

    csvp.parse();
    std::vector<Node*> nodes = csvp.GetNodes();
    std::vector<Edge*> edges = csvp.GetEdges();
        
    std::cout << nodes.size() << " nodes parsed" << std::endl;
    std::cout << edges.size() << " edges parsed" << std::endl;    

    std::vector<std::vector<double>> directed = csvp.GetAdjacencyMatrixDirected();
    std::vector<std::vector<double>> undirected = csvp.GetAdjacencyMatrixUndirected();
    std::map<int, int> index_map = csvp.GetAdjacencyIndexMap();

    Edge* edge = edges[0];
    int from_node = edge->fromNode();
    int to_node = edge->toNode();
    int km = edge->km();

    // std::cout << km << " value from edges array" << std::endl;
    // std::cout << directed[from_node][to_node] << " value from adjacency matrix" << std::endl;

    return 0;
}