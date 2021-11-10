#include "../include/adder.h"

using Parser::Node;

namespace Adder {
    
    Adder::Adder(Node n, Node n2) {
        result_ = n.getData() + n2.getData();
    }

    std::string Adder::getResult() {
        return result_;
    }
}