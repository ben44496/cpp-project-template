#include <catch2/catch.hpp>
#include "../../parsing/include/node.h"
#include "../include/GraphTraversal.h"
#include "../include/BFS.h"

using Parser::Node;

TEST_CASE("BFS maintains ordering") {    
    Node* node = new Node(100, 200, 14512, "USA", "CA", 9);
    Node* connection_one = new Node(200, 340, 16782, "USA", "AZ", 10);
    Node* connection_two = new Node(200, 340, 78954, "USA", "PHX", 7);
    BFS bfs(node);

    node->addOutboundEdge(connection_one, 103);
    connection_one->addOutboundEdge(connection_two, 200);

    auto it = bfs.begin();
    REQUIRE((*it)->getId() == 14512);
    ++it;
    REQUIRE((*it)->getId() == 16782);
    ++it;
    REQUIRE((*it)->getId() == 78954);
}

TEST_CASE("BFS ordering on single node") {    
    Node* node = new Node(100, 200, 14512, "USA", "CA", 9);        
    BFS bfs(node);

    auto it = bfs.begin();
    REQUIRE((*it)->getId() == 14512);
}

TEST_CASE("BFS on cycle terminates") {
    Node* node = new Node(100, 200, 14512, "USA", "CA", 9);        
    node->addOutboundEdge(node, 100);
    BFS bfs(node);    

    auto it = bfs.begin();
    REQUIRE((*it)->getId() == 14512);
}

TEST_CASE("BFS peek doesn't remove node") {
    Node* node = new Node(100, 200, 14512, "USA", "CA", 9);        
    node->addOutboundEdge(node, 100);
    BFS bfs(node);    

    Node* n = bfs.peek();
    
    REQUIRE(!bfs.empty());
}

TEST_CASE("BFS empty after iterating across all elements") {
    Node* node = new Node(100, 200, 14512, "USA", "CA", 9);
    Node* connection_one = new Node(200, 340, 16782, "USA", "AZ", 10);
    Node* connection_two = new Node(200, 340, 78954, "USA", "PHX", 7);
    BFS bfs(node);

    node->addOutboundEdge(connection_one, 103);
    connection_one->addOutboundEdge(connection_two, 200);

    auto it = bfs.begin();    
    ++it;    
    ++it;   

    REQUIRE(bfs.empty());
}

TEST_CASE("BFS popping removes element") {
    Node* node = new Node(100, 200, 14512, "USA", "CA", 9);
    BFS bfs(node);

    REQUIRE(bfs.pop()->getId() == 14512);
    REQUIRE(bfs.empty());
}

TEST_CASE("BFS peeking doesn't remove element") {
    Node* node = new Node(100, 200, 14512, "USA", "CA", 9);
    BFS bfs(node);

    REQUIRE(bfs.peek()->getId() == 14512);
    REQUIRE(!bfs.empty());
}

TEST_CASE("BFS peeking multiple times results in same element") {
    BFS bfs;
    Node* node = new Node(100, 200, 14512, "USA", "CA", 9);
    Node* node_one = new Node(100, 200, 1500, "USA", "CA", 9);
    Node* node_two = new Node(100, 200, 1600, "USA", "CA", 9);
    Node* node_three = new Node(100, 200, 1700, "USA", "CA", 9);
    bfs.add(node);
    bfs.add(node_one);
    bfs.add(node_two);
    bfs.add(node_three);  

    REQUIRE(bfs.peek()->getId() == 14512);
    REQUIRE(bfs.peek()->getId() == 14512);    
}

TEST_CASE("BFS add method") {
    BFS bfs;
    Node* node = new Node(100, 200, 14512, "USA", "CA", 9);
    bfs.add(node);

    REQUIRE(bfs.pop()->getId() == 14512);
}

TEST_CASE("BFS adding multiple nodes") {
    BFS bfs;
    Node* node = new Node(100, 200, 14512, "USA", "CA", 9);
    Node* node_one = new Node(100, 200, 1500, "USA", "CA", 9);
    Node* node_two = new Node(100, 200, 1600, "USA", "CA", 9);
    Node* node_three = new Node(100, 200, 1700, "USA", "CA", 9);
    bfs.add(node);
    bfs.add(node_one);
    bfs.add(node_two);
    bfs.add(node_three);    

    REQUIRE(bfs.pop()->getId() == 14512);
    REQUIRE(bfs.pop()->getId() == 1500);
    REQUIRE(bfs.pop()->getId() == 1600);
    REQUIRE(bfs.pop()->getId() == 1700);
}

TEST_CASE("Empty on non-empty BFS") {
    Node* node = new Node(100, 200, 14512, "USA", "CA", 9);
    BFS bfs(node);
    
    REQUIRE(!bfs.empty());
}

TEST_CASE("Empty on empty BFS") {    
    BFS bfs;
    
    REQUIRE(bfs.empty());
}