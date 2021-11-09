#include "catch2/catch.hpp"

#include "../include/parser_header.h"
using Parser::Node;

TEST_CASE("Test node") {
    SECTION("Adding outbound edge") {
        Node* new_node = new Node(100, -100, 10456, "USA", "CA", 43);
        Node* edge_node = new Node(100, -120, 10412, "USA", "CA", 44);
        new_node->addOutboundEdge(edge_node, 1.02);

        std::vector<std::tuple<Node*, float>> res = new_node->getOutbound();
        
        REQUIRE(std::get<0>(res[0]) == edge_node);
        REQUIRE(std::get<1>(res[0]) == 1.02f);
    }

    SECTION("Test spatial information") {
        Node* new_node = new Node(100, -100, 10456, "USA", "CA", 43);

        std::tuple<double, double> res = new_node->getLoc();

        REQUIRE(std::get<0>(res) == 100);
        REQUIRE(std::get<1>(res) == -100);
    }

    SECTION("Test print") {
        Node* new_node = new Node(100, -100, 10456, "USA", "CA", 43);

        std::string res = new_node->print();
        std::string expected = "ID: 10456\n"
                                "Lat: 100.000000\n"
                                "Long: -100.000000\n"
                                "Country: USA\n"
                                "State: CA\n"
                                "District: 43\n"
                                "Outbound Edges: 0\n";

        REQUIRE(res == expected);
    }
}