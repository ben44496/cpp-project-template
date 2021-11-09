/**
 * @file BFS.h
 */

#pragma once

#include <iterator>
#include <cmath>
#include <list>
#include <queue>

#include "GraphTraversal.h"

/**
 * A breadth-first GraphTraversal.
 * Derived from base class GraphTraversal
 */
class BFS : public GraphTraversal {
  public:
    // Constructors
    BFS() {};
    BFS(Node* node);

    // Iterator
    GraphTraversal::Iterator begin();
    GraphTraversal::Iterator end();

    // Functions
    void add(Node* node);
    Node* pop();
    Node* peek() const;
    bool empty() const;

  private:
    std::queue<Node*> to_visit;

    Node* start_;        
    Node* current_; 
};