#include "include/AStarAlgorithm.h"
#include <iostream>

#include <cmath>
#include <algorithm>
#include <deque>
#include <stdexcept>

AStarAlgorithm::AStarAlgorithm(const vector<Node*> & graph, int start, int end){
    if(start < 0 || start >= graph.size() || end < 0 || end >= graph.size())
        throw std::invalid_argument("Start or End index is invalid");
    graph_ = graph;
    visited_ = vector<bool>(graph.size(), false);
    local_dist_ = vector<float>(graph.size(), INFINITY);
    global_dist_ = vector<float>(graph.size(), INFINITY);
    parents_ = vector<int>(graph.size(), -1);

    start_pos_ = start;
    end_pos_ = end;

    for(size_t i = 0; i < graph_.size(); i++){
        id_to_index_[graph_[i]->getId()] = i;
    }
       
}
 
void AStarAlgorithm::SolveAStar() {

    Node *current = graph_[start_pos_];
    local_dist_[start_pos_] = 0.0f;

    global_dist_[start_pos_] = heuristic(graph_[start_pos_],  graph_[end_pos_]);

    std::deque<Node*> not_tested_nodes_list;
    not_tested_nodes_list.push_back(graph_[start_pos_]);

    while (!not_tested_nodes_list.empty()){

        //Sort not tested nodes by distance from end point
        for (size_t i = 0; i < not_tested_nodes_list.size() - 1; i++)
            for (size_t j = 0; j < not_tested_nodes_list.size()-i-1; j++){
                int ind1 = id_to_index_[not_tested_nodes_list[j]->getId()];
                int ind2 = id_to_index_[not_tested_nodes_list[j+1]->getId()];
                 if (global_dist_[ind1] > global_dist_[ind2]){
                    Node* temp = not_tested_nodes_list[j];
                    not_tested_nodes_list[j] = not_tested_nodes_list[j+1];
                    not_tested_nodes_list[j+1] = temp;
                 }
        }

        while(!not_tested_nodes_list.empty() && visited_[id_to_index_[not_tested_nodes_list.front()->getId()]]) 
            not_tested_nodes_list.pop_front();

        if (not_tested_nodes_list.empty())
            break;

        current = not_tested_nodes_list.front();
        size_t curr_pos = id_to_index_[current->getId()];
        visited_[curr_pos] = true;
        auto neighbors = current->getOutbound();

        for (auto node_neighbor_tuple : neighbors){
            Node* node_neighbor = std::get<0>(node_neighbor_tuple);
            size_t neighbor_pos = id_to_index_[node_neighbor->getId()];

            if (!visited_[neighbor_pos])
                not_tested_nodes_list.push_back(graph_[neighbor_pos]);

            float possible_lower_goal = local_dist_[curr_pos] + std::get<1>(node_neighbor_tuple);

            if (possible_lower_goal < local_dist_[neighbor_pos])
            {
                parents_[neighbor_pos] = curr_pos;
                local_dist_[neighbor_pos] = possible_lower_goal;

                global_dist_[neighbor_pos] = local_dist_[neighbor_pos] + heuristic(graph_[end_pos_], node_neighbor);
            }
        }
    }
    UpdateSolution();
}

void AStarAlgorithm::UpdateSolution(){
    auto itr_pos = end_pos_;

    while (parents_[itr_pos] != -1){
        solution_.push_back(graph_[itr_pos]->getId());
        itr_pos = parents_[itr_pos];
    }
    solution_.push_back(graph_[itr_pos]->getId());

    std::reverse(solution_.begin(), solution_.end());
}

double AStarAlgorithm::heuristic(Node* first, Node* second){
    auto loc1 = first->getLoc();
    auto loc2 = second->getLoc();

    return distance(std::get<0>(loc1), std::get<1>(loc1), std::get<0>(loc2), std::get<1>(loc2));
}

vector<int> AStarAlgorithm::GetSolution() const {
    return solution_;
}

double AStarAlgorithm::distance(double lat1, double long1, double lat2, double long2){
    lat1 = toRadians(lat1);
    long1 = toRadians(long1);
    lat2 = toRadians(lat2);
    long2 = toRadians(long2);
     
    double dlong = long2 - long1;
    double dlat = lat2 - lat1;
 
    double ans = pow(sin(dlat / 2), 2) +
                          cos(lat1) * cos(lat2) *
                          pow(sin(dlong / 2), 2);
 
    ans = 2 * asin(sqrt(ans));

    return ans * 6371;
}

double AStarAlgorithm::toRadians(const double degree){
    double one_deg = (M_PI) / 180;
    return (one_deg * degree);
}