#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "parser_header.h"
#include "GraphTraversal.h"
#include "BFS.h"

/**
 * Initializes a breadth-first GraphTraversal on the given Node,
 * starting at `Node*`. 
 * @param node The start Node* of this BFS
 */
BFS::BFS(Node* node) {    
    start_ = node;

    to_visit.push(start_);    
}

/**
 * Returns an iterator for the traversal starting at the first Node*.
 */
GraphTraversal::Iterator BFS::begin() {
  return GraphTraversal::Iterator(this, start_);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
GraphTraversal::Iterator BFS::end() {
  return GraphTraversal::Iterator();
}

/**
 * Adds a Node* for the traversal to visit at some Node* in the future.
 */
void BFS::add(Node* node) {
  to_visit.push(node);  
}

/**
 * Removes and returns the current Node* in the traversal.
 */
Node* BFS::pop() {
  current_ = to_visit.front();
  to_visit.pop();
  return current_;
}

/**
 * Returns the current Node* in the traversal.
 */
Node* BFS::peek() const {
  return to_visit.front();
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  return to_visit.empty();
}