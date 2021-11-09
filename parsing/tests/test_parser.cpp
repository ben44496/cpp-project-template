#include "catch2/catch.hpp"
#include <unistd.h>
#include "../include/parser_header.h"
#include "include/edge.h"
using Parser::CSVParser;
using Parser::Node;
using Parser::Edge;

TEST_CASE("Parsing nodes_test.csv") {
    // TODO: Redo testing to reflect new changes.
    SECTION("Size of nodes vector is accurate") {
        CSVParser parser("tests/data/nodes_test.csv", "tests/data/edges_test.csv"); // create parser object
        parser.parse();

        std::vector<Node*> res = parser.GetNodes();
        REQUIRE(res.size() == 12);
    }

    SECTION("Last node is accurate") {
        CSVParser parser("tests/data/nodes_test.csv", "tests/data/edges_test.csv"); // create parser object
        parser.parse();

        std::string res = parser.print();
        std::string expected = "ID: 600000\n"
                                "Lat: -135.067308\n"
                                "Long: 60.737040\n"
                                "Country: CA\n"
                                "State: YT\n"
                                "District: 99\n"
                                "Outbound Edges: 0\n";
        REQUIRE(res == expected);
    }

    SECTION("First node is accurate") {
        CSVParser parser("tests/data/nodes_test.csv", "tests/data/edges_test.csv"); // create parser object
        parser.parse();

        std::vector<Node*> nodes = parser.GetNodes();
        Node* node = nodes.front();
        std::string res = node->print();
        std::string expected = "ID: 300500\n"
                                "Lat: -135.317131\n"
                                "Long: 59.452500\n"
                                "Country: US\n"
                                "State: AK\n"
                                "District: 8\n"
                                "Outbound Edges: 0\n";
        REQUIRE(res == expected);
    }

    SECTION("Middle node is accurate") {
        CSVParser parser("tests/data/nodes_test.csv", "tests/data/edges_test.csv"); // create parser object
        parser.parse();

        std::vector<Node*> nodes = parser.GetNodes();
        Node* node = nodes[6];
        std::string res = node->print();
        std::string expected = "ID: 300506\n"
                                "Lat: -135.293453\n"
                                "Long: 59.470097\n"
                                "Country: US\n"
                                "State: AK\n"
                                "District: 8\n"
                                "Outbound Edges: 0\n";
        REQUIRE(res == expected);
    }

    SECTION("Outbound edge between two nodes contains correct node ID's") {
        CSVParser parser("tests/data/nodes_test.csv", "tests/data/edges_test.csv"); // create parser object
        parser.parse();

        std::vector<Edge*> edges = parser.GetEdges();
        Edge* edge = edges[0];
        
        REQUIRE(edge->fromNode() == 348741);
        REQUIRE(edge->toNode() == 348746);        
    }

    SECTION("Outbound edge between two nodes contains correct weight of route") {
        CSVParser parser("tests/data/nodes_test.csv", "tests/data/edges_test.csv"); // create parser object
        parser.parse();

        std::vector<Edge*> edges = parser.GetEdges();
        Edge* edge = edges[0];
        
        REQUIRE(edge->km() == 0.28662579);                
    }

    SECTION("# of total edges is correct") {
        CSVParser parser("tests/data/nodes_test.csv", "tests/data/edges_test.csv"); // create parser object
        parser.parse();

        std::vector<Edge*> edges = parser.GetEdges();        
        
        REQUIRE(edges.size() == 12);  
    }

    SECTION("# of rows is accurate") {
        CSVParser parser("tests/data/nodes_test.csv", "tests/data/edges_test.csv"); // create parser object
        parser.parse();

        REQUIRE(parser.rows() == 12);
    }

    SECTION("Unparsed data does not cause problems with rows") {
        CSVParser parser("tests/data/nodes_test.csv", "tests/data/edges_test.csv"); // create parser object

        REQUIRE(parser.rows() == 0);
    }
}

