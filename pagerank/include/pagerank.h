#pragma once

#include <vector>
#include <map>

using std::vector;
using std::map;
using std::string;

class PageRank {
    public:
        PageRank(vector<vector<float>> weights, map<int, int> column_names);
        map<int, float> solve();
        std::pair<int, float> best_rank();

        float norm_ = 2;
        float tolerance_ = 0.000001;
        int max_iter_ = 1000;
        float alpha_ = 0.95;

    private:
        vector<vector<float>> weights_;
        map<int, int> id_to_col_;
        map<int, int> col_to_id_;
        map<int, float> solution_;
        int size_;

        vector<float> markov_step(const vector<float>& vec);
        float distance(const vector<float>& vec1, const vector<float>& vec2, int norm);
        void construct_markov_matrix();
};