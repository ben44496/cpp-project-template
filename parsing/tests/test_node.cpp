#include "catch2/catch.hpp"

#include "../include/node.h"

using Parser::Node;

TEST_CASE("Node tests") {
    SECTION("Test constructor", "[nodes]") {
        Node n("1");

        REQUIRE(n.getID() == 0);
        REQUIRE(n.getData() == "1");
    }

    SECTION("Test static counter num_nodes_ on stack", "[nodes]") {
        REQUIRE(Node::num_nodes_ == 0);
        Node n("abc");

        REQUIRE(Node::num_nodes_ == 1);
        REQUIRE(n.getID() == 0);

        Node n2("123");

        REQUIRE(Node::num_nodes_ == 2);
        REQUIRE(n2.getID() == 1);
    }
}