#include "catch2/catch.hpp"
#include "include/adder.h"

using Parser::Node;

TEST_CASE("Adder Tests") {
    SECTION("Sanity check", "[adder]") {
        Node n("1");
        Node n2("2");
        Adder::Adder a(n, n2);

        REQUIRE(a.getResult() == "12");
        // REQUIRE(Node::num_nodes_ == 2);
    }
}