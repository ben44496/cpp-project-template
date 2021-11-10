#pragma once

#include "parser_header.h"
#include <string>

using Parser::Node;

namespace Adder {
class Adder {
    public:
        Adder(Node n, Node n2);
        std::string getResult();

    private:
        std::string result_ = "";
};
}