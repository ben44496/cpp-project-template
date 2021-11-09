//
// Created by Tarun Voruganti on 11/24/20.
//

#ifndef PATH_FINDING_ASTARALGORITHM_H
#define PATH_FINDING_ASTARALGORITHM_H

#include "parser_header.h"
#include <vector>
#include <list>
#include <cmath>
#include <map>

using Parser::Node;
using std::vector;
using std::map;

class AStarAlgorithm {

public:
  AStarAlgorithm() = default;

  /**
   * Creates An array of nodes given a 2D vector of characters
   * @param graph       2D Vector of Chars
   * @param start_pos   Position of start point in the graph
   * @param end_pos     Position of end point in the graph
   */

  AStarAlgorithm(const vector<Node*> & graph, int start, int end);

  /**
   * Finds a path from the start point to end point
   */
  void SolveAStar();

  /**
   * Returns the map held by the algorithm, whether solved or unsolved
   * @return the map
   */
  vector<int> GetSolution() const;

private:
  struct NodeI {
    size_t x;              // x position
    size_t y;              // y position
    vector<NodeI *> neighbors; // Connections to neighbours
  };

  vector<bool> visited_;
  vector<float> local_dist_;
  vector<float> global_dist_;
  vector<int> parents_;
  vector<int> solution_;
  vector<Node*> graph_;
  int start_pos_;
  int end_pos_;
  map<int, int> id_to_index_;

  /**
   * After Solving the algorithm, it updates the 2D vector of chars to show the path found by the algo
   */
  void UpdateSolution();

  double heuristic(Node* first, Node* second);

  double distance(double lat1, double long1, double lat2, double long2);

  double toRadians(const double deg);

};

#endif // PATH_FINDING_ASTARALGORITHM_H
