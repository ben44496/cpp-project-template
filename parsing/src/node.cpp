#include "../include/node.h"

using std::string;

namespace Parser {
    unsigned Node::num_nodes_;
    
    Node::Node(string data) {
        id_ = num_nodes_++;
        data_ = data;
    }

    Node::~Node() {
        num_nodes_--;
    }

    unsigned Node::getID() {
        return id_;
    }

    string Node::getData() {
        return data_;
    }
}