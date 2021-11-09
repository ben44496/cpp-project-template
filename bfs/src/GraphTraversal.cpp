#include "../include/GraphTraversal.h"

/**
 * Default iterator constructor.
 */
GraphTraversal::Iterator::Iterator() : traversal_(nullptr) {}

/**
 * Adds all outbound edge nodes to the traversal. 
 */ 
void GraphTraversal::Iterator::AddNeighbors(Node* node) {  
  std::vector<std::tuple<Node*, float>> outbound = node->getOutbound();

  for (std::tuple<Node*, float> edge : outbound) {
      Node* node = std::get<0>(edge);

      traversal_->add(node);
  }
}

bool GraphTraversal::Iterator::ShouldVisit(Node* node) {
  // check if already visited
  size_t key = node->getId();
  if (visited.find(key) != visited.end())
    return false;

  return true;
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal to the next outbound edge of the current node.
 */
GraphTraversal::Iterator & GraphTraversal::Iterator::operator++() {
    // mark current point as visited
    size_t key = current_->getId();
    visited.insert(key);

    // add all possible neighbors    
    AddNeighbors(current_);        

    Node* tmp = traversal_->peek();
    while (tmp != nullptr && !(ShouldVisit(tmp))) {      
      if (!(traversal_->empty()))
        tmp = traversal_->pop();
      else {
        traversal_ = nullptr;
        return *this;
      }
    }

    if (tmp == nullptr) {
      traversal_ = nullptr;
      return *this;
    }
        
    current_ = tmp;
    return *this;

}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Node* in the GraphTraversal.
 */
Node* GraphTraversal::Iterator::operator*() {
  return current_;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool GraphTraversal::Iterator::operator!=(const GraphTraversal::Iterator &other) {
  return !(traversal_ == nullptr && other.traversal_ == nullptr);
}