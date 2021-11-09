#include "catch2/catch.hpp"
#include "include/AStarAlgorithm.h"

TEST_CASE("Tests") {
    SECTION("Test Exception"){
        Node* node1 = new Node(87,  45, 12, "country", "state", 4);

        Node* node2 = new Node(50,  3, 46, "country", "state", 4);

        Node* node3 = new Node(19,  38, 15, "country", "state", 4);

        node1->addOutboundEdge(node2, 1);

        node2->addOutboundEdge(node3, 1);
        node2->addOutboundEdge(node1, 1);

        node3->addOutboundEdge(node2, 1);

        vector<Node *> vec = {node1, node2, node3};

        using alg = AStarAlgorithm;
        REQUIRE_THROWS_AS(alg(vec, 0, 4), std::invalid_argument);
    }

    SECTION("Basic Test 1") 
    {
        Node* node1 = new Node(87,  45, 12, "country", "state", 4);

        Node* node2 = new Node(50,  3, 46, "country", "state", 4);

        Node* node3 = new Node(19,  38, 15, "country", "state", 4);

        node1->addOutboundEdge(node2, 1);

        node2->addOutboundEdge(node3, 1);
        node2->addOutboundEdge(node1, 1);

        node3->addOutboundEdge(node2, 1);

        vector<Node *> vec = {node1, node2, node3};

        AStarAlgorithm alg = AStarAlgorithm(vec, 0, 2);
        alg.SolveAStar();
        auto sol = alg.GetSolution();

        REQUIRE(sol[0] == 12);
        REQUIRE(sol[1] == 46);
        REQUIRE(sol[2] == 15);
    }

    SECTION("Basic Test 2"){
        Node* node1 = new Node(87,  45, 12, "country", "state", 4);

        Node* node2 = new Node(50,  3, 46, "country", "state", 4);

        Node* node3 = new Node(19,  38, 15, "country", "state", 4);

        Node* node4 = new Node(40,  12, 23, "country", "state", 4);

        node1->addOutboundEdge(node2, 1);
        node1->addOutboundEdge(node4, 100);

        node2->addOutboundEdge(node3, 1);
        node2->addOutboundEdge(node1, 1);

        node3->addOutboundEdge(node2, 1);
        node3->addOutboundEdge(node4, 1);

        node4->addOutboundEdge(node3, 1);
        node4->addOutboundEdge(node1, 100);

        vector<Node *> vec = {node1, node2, node3, node4};

        AStarAlgorithm alg = AStarAlgorithm(vec, 0, 3);
        alg.SolveAStar();
        auto sol = alg.GetSolution();

        REQUIRE(sol[0] == 12);
        REQUIRE(sol[1] == 46);
        REQUIRE(sol[2] == 15);
        REQUIRE(sol[3] == 23);
    }

}