#include "include/node.h"
#include <iostream>


int main() {
    Parser::Node n("5");
    Parser::Node n2("6");

    std::cout << n.getID() << ", " << n.getData() << std::endl;
    std::cout << n2.getID() << ", " << n2.getData() << std::endl;
    std::cout << Parser::Node::num_nodes_ << std::endl;
}