#include "../include/parser.h"
#include <fstream>

using std::vector;
using std::string;
using std::fstream;
using std::ios;

using Parser::Node;


namespace Parser {

CSVParser::CSVParser(const string& nodes_file, const string& edges_file) : nodes_file_(nodes_file), edges_file_(edges_file) {}

CSVParser::CSVParser(const CSVParser& other) {
    *this = other;
}

CSVParser& CSVParser::operator=(const CSVParser& other) {
    if (this != &other) {
        delete this;
        for (auto node : other.nodes_) {
            nodes_.push_back(new Node(*node));
        }

        for (auto edge : other.edges_) {
            // TODO: Do I implement edges?
        }

        nodes_file_ = other.nodes_file_;
        edges_file_ = other.edges_file_;
    }
    return *this;
}

CSVParser::~CSVParser() {
    // Delete data_ Node* vector
    // Could also probably just be data_.erase()
    for (auto node : nodes_) {
        delete node;
    }
    nodes_.clear();

    for (auto edge: edges_) {
        delete edge;
    }
    edges_.clear();
}

void CSVParser::parse() {
    nodes_ = parseNodes(nodes_file_);
    edges_ = parseEdges(edges_file_);
}

vector<Node*> CSVParser::parseNodes(const string& nodes_file) {
    fstream newfile;
    string delimiter = ",";

    vector<Node*> data;

    if (nodes_file.empty()) {
        std::cout << "Please input a file path" << std::endl;
        return data;
    }

    newfile.open(nodes_file, ios::in);

    bool first_line = true;
    if (newfile.is_open()) {
        string datapoint;

        while (getline(newfile, datapoint)) {
            // std::cout << "line found" << std::endl;

            if (first_line) {
                first_line = false;
                continue;
            }   
            
            int pos = 0;
            string token;
            vector<string> elems;

            while ((pos = datapoint.find(delimiter)) != std::string::npos) {
                token = datapoint.substr(0, pos);
                elems.push_back(token);
                datapoint.erase(0, pos + 1);
            }

            elems.push_back(datapoint);

            if (!datapoint.empty()) {
                // Construct Nodes*
                double latitude = std::stod(elems.at(0));
                double longitude = std::stod(elems.at(1));
                int id =  std::stoi(elems.at(2));
                string country = elems.at(3);
                string state = elems.at(4);
                int district = std::stoi(elems[5]);

                Node* new_node = new Node(latitude, longitude, id, country, state, district);

                data.push_back(new_node);
                nodes_map_[id] = new_node;
            } else {
                std::cout << "datapoint is empty" << std::endl;
            }
        }
    } else {
        std::cout << "error opening file" << std::endl;        
    }

    return data;
}

vector<Edge*> CSVParser::parseEdges(const string& edges_file) {
    fstream newfile;
    string delimiter = ",";

    vector<Edge*> data;

    if (edges_file.empty()) {
        std::cout << "Please input a file path" << std::endl;
        return data;
    }

    // std::cout << " starting to make vectors " << std::endl;

    // int size = nodes_.size();
    // adjacency_matrix_directed_.resize(size);
    // for (int i = 0; i < adjacency_matrix_directed_.size(); i++) {
    //     adjacency_matrix_directed_[i].resize(size);
    // }
    
    // std::cout << " first vector done " << std::endl;

    // adjacency_matrix_undirected_.resize(size);
    // for (int i = 0; i < adjacency_matrix_undirected_.size(); i++) {
    //     adjacency_matrix_undirected_[i].resize(size);
    // }

    // for (int i = 0; i < nodes_.size(); i++) {
    //     Node* node = nodes_[i];
    //     int id = node->getId();
    //     adjacency_index_map_[id] = i;
    // }    

    // std::cout << " done making vectors " << std::endl;

    newfile.open(edges_file, ios::in);

    bool first_line = true;
    int i = 0;
    if (newfile.is_open()) {
        string datapoint;

        while (getline(newfile, datapoint)) {
            if (first_line) {
                first_line = false;
                continue;
            } 

            int pos = 0;
            string token;
            vector<string> elems;            

            while ((pos = datapoint.find(delimiter)) != std::string::npos) {
                token = datapoint.substr(0, pos);
                elems.push_back(token);
                datapoint.erase(0, pos + 1);
            }

            elems.push_back(datapoint);

            if (!datapoint.empty()) {
                // Construct Nodes*
                int route_id = std::stoi(elems.at(0));
                int from_node = std::stoi(elems.at(1));
                int to_node =  std::stoi(elems.at(2));
                string state = elems.at(3);
                string country = elems.at(4);
                double km = std::stod(elems.at(5));                

                Edge* new_edge = new Edge(route_id, from_node, to_node, state, country, km);
                                
                // int from_matrix_index = adjacency_index_map_[from_node];
                // int to_matrix_index = adjacency_index_map_[to_node];
                // adjacency_matrix_directed_[from_matrix_index][to_matrix_index] = km;
                // adjacency_matrix_undirected_[from_matrix_index][to_matrix_index] = km;
                // adjacency_matrix_undirected_[to_matrix_index][from_matrix_index] = km;

                if (nodes_map_.find(from_node) != nodes_map_.end() && nodes_map_.find(to_node) != nodes_map_.end()) {
                    nodes_map_[from_node]->addOutboundEdge(nodes_map_[to_node], km);
                    nodes_map_[to_node]->addInboundEdge(nodes_map_[from_node], km);
                } else {
                    i++;
                }                         

                data.push_back(new_edge);
            } else {
                std::cout << "datapoint is empty" << std::endl;
            }
        }
    }

    // std::cout << "Parsed edges: " << i << " edges were missing a node entry" << std::endl;

    return data;
}

string CSVParser::print() {
    // TODO: Finish implementing print given modulus, using overload << Node`    
    if (nodes_.size() != 0) {
        // string output;
        Node* node = nodes_.at(nodes_.size() - 1);
        return node->print();
    }

    return "";
}

std::vector<std::vector<double>> CSVParser::GetAdjacencyMatrixDirected() {
    return adjacency_matrix_directed_;
}

std::vector<std::vector<double>> CSVParser::GetAdjacencyMatrixUndirected() {
    return adjacency_matrix_undirected_;
}

std::map<int, int> CSVParser::GetAdjacencyIndexMap() {
    return adjacency_index_map_;
}

vector<Node*> CSVParser::GetNodes() {
    return this->nodes_;
}

vector<Edge*> CSVParser::GetEdges() {
    return this->edges_;
}

int CSVParser::rows() { return nodes_.size(); }

}