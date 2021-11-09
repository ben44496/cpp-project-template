#include <cmath>
#include <iostream>
#include "../include/pagerank.h"

PageRank::PageRank(vector<vector<float>> weights, map<int, int> column_names) {
    if (weights.size() == 0 || weights.size() != weights[0].size()) {
        throw "Non-square weights matrix";
    }
    if (column_names.size() != weights.size()) {
        throw "Incorrect column names size";
    }
    size_ = weights.size();
    id_to_col_ = column_names;
    for (auto p : id_to_col_) {
        col_to_id_.insert(std::pair<int, int>(p.second, p.first));
    }
    weights_ = weights;
    construct_markov_matrix();
}

map<int, float> PageRank::solve() {
    if (!solution_.empty()) {
        return solution_;
    }
    vector<float> prev(size_, 1/(float)size_);
    vector<float> curr = markov_step(prev);
    float dist = distance(prev, curr, norm_);
    int iter = 0;

    while (dist > tolerance_ && iter < max_iter_) {
        prev = curr;
        curr = markov_step(curr);
        dist = distance(prev, curr, norm_);
        ++iter;
    }

    solution_.clear();
    for (int i = 0; i < size_; ++i) {
        solution_.insert(std::pair<int, float>(col_to_id_[i], curr[i]));
    }

    return solution_;
}

std::pair<int, float> PageRank::best_rank() {
    if (solution_.empty()) {
        solve();
    }
    std::pair<int, float> max;
    for (auto p : solution_) {
        if (p.second > max.second) {
            max = p;
        }
    }
    return max;
}

vector<float> PageRank::markov_step(const vector<float>& vec) {
    vector<float> result(size_, 0);
    float total;
    for (int i = 0; i < size_; ++i) {
        for (int j = 0; j < size_; ++j) {
            result[i] += weights_[i][j] * vec[j];
        }
        result[i] = result[i]*alpha_ + (1-alpha_);
        total += result[i];
    }
    for (int i = 0; i < size_; ++i) {
        result[i] /= total;
    }
    return result;
}

float PageRank::distance(const vector<float>& vec1, const vector<float>& vec2, int norm) {
    float total = 0;
    for (size_t i = 0; i < vec1.size(); ++i) {
        total += std::pow(vec2[i] - vec1[i], norm);
    }
    return std::pow(total, 1/(float)norm);
}

void PageRank::construct_markov_matrix() {
    for (size_t j = 0; j < size_; ++j) {
        float column_total = 0;
        for (size_t i = 0; i < size_; ++i) {
            column_total += weights_[i][j];
        }
        for (size_t i = 0; i < size_; ++i) {
            if (column_total > 0) {
                weights_[i][j] /= column_total;
            } else {
                weights_[i][j] = 1/(float)size_;
            }
        }
    }
}
