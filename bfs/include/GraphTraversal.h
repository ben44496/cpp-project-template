/**
 * @file GraphTraversal.h
 */
#pragma once

#include <iterator>
#include <unordered_set>
#include <string>
#include "../../parsing/include/node.h"
#include <cmath>
#include <iterator>
#include <iostream>

/**
 * A base class for traversal algorithms on images.
 *
 * BFS and DFS will inherit from this class
 * 
 * Each derived class must maintain an ordering of points on an image,
 * through calls to the virtual member functions `add` and `pop`.
 * 
 * A derived class provides a traversal by returning instances of
 * ImageTraversal::Iterator.
 */

using Parser::Node;

/**
 * Holds the Iterator and GraphTraversal type for the traversal
 */
class GraphTraversal {
  public:
    /**
     * A forward iterator through an ImageTraversal.
     */
    class Iterator : std::iterator<std::forward_iterator_tag, Node*> {

  public:
    // Iterator Constructors
    Iterator();
    Iterator(GraphTraversal* traversal, Node* current) : traversal_(traversal) {      
      current_ = current;

      size_t key = current->getId();
      visited.insert(key);
      
      AddNeighbors(current_);
    }

    // Operators
    Iterator & operator++();
    Node* operator*();
    bool operator!=(const Iterator &other);

    // Public functions
    void AddNeighbors(Node* point);
    bool ShouldVisit(Node* p);

  private:
    // Stores the current node in the traversal
    Node* current_;

    // Keeps track of visited nodes
    std::unordered_set<size_t> visited;

    // Records which traversal 
    GraphTraversal* traversal_;        

  };

  /**
   * The begining of an iterator
   * Virtual function. Derived class need to implement this.
   */
  virtual Iterator begin() = 0;

  /**
   * The end of an iterator. Checks if traversal_ is nullptr.
   * Virtual function. Derived class need to implement this.
   */
  virtual Iterator end() = 0;

  /**
   * Add new point to the traversal
   * Virtual function. Derived class need to implement this.
   */
  virtual void add(Node* node) = 0;

  /**
   * Remove and return the next point of the traversal
   * Virtual function. Derived class need to implement this.
   */
  virtual Node* pop() = 0;

  /**
   * Return but not remove the next point of the traversal
   * Virtual function. Derived class need to implement this.
   */
  virtual Node* peek() const = 0;

  /**
   * To see if the traversal has no points left
   * Virtual function. Derived class need to implement this.
   */
  virtual bool empty() const = 0;
};