#include "util.h"
#include "parser_header.h"
#include "BFS.h"
#include "AStarAlgorithm.h"
#include "pagerank.h"

#include <string>
#include <fstream>
#include <unordered_set>
#include <cmath>

using namespace Parser;
using util::OptionsParser;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::unordered_set;


namespace opts
{
    bool help = false;
}

int main(int argc, const char** argv) {
    string nodesFile = "../data/nodes.csv";
    string edgesFile = "../data/edges.csv";
    
    OptionsParser optsparse;
    optsparse.addArg(nodesFile);
    optsparse.addArg(edgesFile);
    optsparse.addOption("help", opts::help);
    optsparse.addOption("h", opts::help);
    optsparse.parse(argc, argv);

    if (opts::help) {
        cout << "Usage: " << argv[0]
             << " [nodes file] [edges file]"
             << endl;
        return 0;
    }

    /* Parsing */
    cout << "Parsing" << endl;
    CSVParser parser(nodesFile, edgesFile);
    parser.parse();

    vector<Node*> nodes = parser.GetNodes();
    vector<Edge*> edges = parser.GetEdges();
    cout << "Number of Nodes: " << nodes.size() << endl;
    cout << "Number of Edges: " << edges.size() << endl;
    cout << endl;

    /* BFS */
    cout << "BFS" << endl;
    BFS bfs(nodes[0]);

    int i = 0;
    for (auto it = bfs.begin(); it != bfs.end(); ++it) {
        std::cout <<"Traversing node with ID: " << (*it)->getId() << std::endl;        
        i++;
    }
    cout << i << " connected nodes" << endl;
    cout << endl;

    /* AStarAlgorithm */
    cout << "A*" << endl;
    AStarAlgorithm astar(nodes, 0, std::min(9, (int) (nodes.size() - 1))); // Indices A to B
    astar.SolveAStar();
    auto sol = astar.GetSolution();

    for(size_t i = 0; i < sol.size(); i++)
        std::cout << sol[i] << " "; // Prints out AStar solution
    cout << endl;
    cout << endl;

    /* PageRank */
    cout << "Pagerank" << endl;
    // Illinois stations
    string filename = "../pagerank/nodes.txt";
    string output_filename = "../pagerank.txt";

    // Open file and read into vector of IDs
    ifstream file;
    file.open(filename);

    if (!file.is_open()) {
        throw "Invalid file";
    }

    unordered_set<int> nodes_laney;
    string node_string;
    while(getline(file, node_string)) {
        nodes_laney.insert(std::stoi(node_string));
    }

    size_t size = nodes_laney.size();

    cout << nodes_laney.size() << " nodes processed for PageRank" << endl;

    // Construct adjacency matrix
    vector<vector<float>> weights(size, vector<float>(size, 0));
    map<int, int> column_names;
    int row = 0;
    for (int n : nodes_laney) {
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
    cout << "Starting PageRank" << endl;
    PageRank pr(weights, column_names);
    map<int, float> result = pr.solve();
    std::pair<int, float> best = pr.best_rank();
    cout << "PageRank complete" << endl;

    // Output solution
    cout << "Top station ID: " << best.first << endl;

    // Output full solution to a file
    ofstream output(output_filename);
    for (auto p : result) {
        output << p.first << " " << p.second << std::endl;
    }
    cout << "Full solution printed to " << "project/pagerank.txt" << endl; // output_filename << endl;

    return 0;
}