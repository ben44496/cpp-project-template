#include "catch2/catch.hpp"
#include "../include/pagerank.h"
#include <cstdlib>

using std::vector;
using std::map;

TEST_CASE("One iteration 2x2 matrix") {
    vector<vector<float>> weights({{1, 0}, {1, 0}});
    map<int, int> id_to_col;
    id_to_col[4] = 0;
    id_to_col[3] = 1;

    PageRank pr(weights, id_to_col);
    pr.norm_ = 2;
    pr.tolerance_ = 0.000001;
    pr.max_iter_ = 1000;
    pr.alpha_ = 0.85;
    map<int, float> result = pr.solve();

    REQUIRE(result.size() == 2);
    REQUIRE(result[4] == 0.5);
    REQUIRE(result[3] == 0.5);
}

TEST_CASE("Simple small matrix") {
    vector<vector<float>> weights({{0.4, 0.3, 0.3}, {0.2, 0.5, 0.2}, {0.4, 0.2, 0.5}});
    map<int, int> id_to_col;
    id_to_col[4] = 0;
    id_to_col[3] = 1;
    id_to_col[2] = 2;

    PageRank pr(weights, id_to_col);
    pr.norm_ = 2;
    pr.tolerance_ = 0.000001;
    pr.max_iter_ = 1000;
    pr.alpha_ = 0.85;
    map<int, float> result = pr.solve();

    REQUIRE(result.size() == 3);
    REQUIRE(result[4] == Approx(0.333333));
    REQUIRE(result[3] == Approx(0.3062201));
    REQUIRE(result[2] == Approx(0.36044657));
}

TEST_CASE("Zero column") {
    vector<vector<float>> weights({{0, 0.3, 0.3}, {0, 0.5, 0.2}, {0, 0.2, 0.5}});
    map<int, int> id_to_col;
    id_to_col[4] = 0;
    id_to_col[3] = 1;
    id_to_col[2] = 2;

    PageRank pr(weights, id_to_col);
    pr.norm_ = 2;
    pr.tolerance_ = 0.000001;
    pr.max_iter_ = 1000;
    pr.alpha_ = 0.85;
    map<int, float> result = pr.solve();

    REQUIRE(result.size() == 3);
    REQUIRE(result[4] == Approx(0.31848));
    REQUIRE(result[3] == Approx(0.34076));
    REQUIRE(result[2] == Approx(0.34076));
}

TEST_CASE("Multiple zero columns") {
    vector<vector<float>> weights({{0, 0.3, 0}, {0, 0.5, 0}, {0, 0.2, 0}});
    map<int, int> id_to_col;
    id_to_col[4] = 0;
    id_to_col[3] = 1;
    id_to_col[2] = 2;

    PageRank pr(weights, id_to_col);
    pr.norm_ = 2;
    pr.tolerance_ = 0.000001;
    pr.max_iter_ = 1000;
    pr.alpha_ = 0.85;
    map<int, float> result = pr.solve();

    REQUIRE(result.size() == 3);
    REQUIRE(result[4] == Approx(0.32518));
    REQUIRE(result[3] == Approx(0.3741));
    REQUIRE(result[2] == Approx(0.30072));
}

TEST_CASE("Column summing to more than one") {
    vector<vector<float>> weights({{4, 0.3, 0.3}, {2, 0.5, 0.2}, {4, 0.2, 0.5}});
    map<int, int> id_to_col;
    id_to_col[4] = 0;
    id_to_col[3] = 1;
    id_to_col[2] = 2;

    PageRank pr(weights, id_to_col);
    pr.norm_ = 2;
    pr.tolerance_ = 0.000001;
    pr.max_iter_ = 1000;
    pr.alpha_ = 0.85;
    map<int, float> result = pr.solve();

    REQUIRE(result.size() == 3);
    REQUIRE(result[4] == Approx(0.333333));
    REQUIRE(result[3] == Approx(0.3062201));
    REQUIRE(result[2] == Approx(0.36044657));
}

TEST_CASE("Multiple columns summing to more than one") {
    vector<vector<float>> weights({{4, 0.3, 3}, {2, 0.5, 2}, {4, 0.2, 5}});
    map<int, int> id_to_col;
    id_to_col[4] = 0;
    id_to_col[3] = 1;
    id_to_col[2] = 2;

    PageRank pr(weights, id_to_col);
    pr.norm_ = 2;
    pr.tolerance_ = 0.000001;
    pr.max_iter_ = 1000;
    pr.alpha_ = 0.85;
    map<int, float> result = pr.solve();

    REQUIRE(result.size() == 3);
    REQUIRE(result[4] == Approx(0.333333));
    REQUIRE(result[3] == Approx(0.3062201));
    REQUIRE(result[2] == Approx(0.36044657));
}

TEST_CASE("Larger matrix") {
    srand(0);
    int size = 30;
    vector<vector<float>> weights;
    for (int i = 0; i < size; ++i) {
        weights.push_back(vector<float>());
        for (int j = 0; j < size; ++j) {
            weights[i].push_back((float)rand()/RAND_MAX);
        }
    }
    map<int, int> column_names;
    for (int i = 0; i < size; ++i) {
        column_names[i] = i;
    }

    PageRank pr(weights, column_names);
    pr.norm_ = 2;
    pr.tolerance_ = 0.000001;
    pr.max_iter_ = 1000;
    pr.alpha_ = 0.85;
    map<int, float> result = pr.solve();

    REQUIRE(result.size() == size);
    
    float total = 0;
    for (int i = 0; i < size; ++i) {
        total += result[i];
    }

    REQUIRE(total == Approx(1));
}

TEST_CASE("Higher first dimension weights matrix") {
    vector<vector<float>> weights({{0.4, 0.3, 0.3}, {0.2, 0.5, 0.2}});
    map<int, int> id_to_col;
    id_to_col[4] = 0;
    id_to_col[3] = 1;
    id_to_col[2] = 2;

    REQUIRE_THROWS(PageRank(weights, id_to_col));
}

TEST_CASE("Higher second dimension weights matrix") {
    vector<vector<float>> weights({{0.4, 0.3}, {0.2, 0.5}, {0.4, 0.2}});
    map<int, int> id_to_col;
    id_to_col[4] = 0;
    id_to_col[3] = 1;

    REQUIRE_THROWS(PageRank(weights, id_to_col));
}

TEST_CASE("Too short column name map") {
    vector<vector<float>> weights({{0.4, 0.3, 0.1}, {0.2, 0.5, 0.8}, {0.4, 0.2, 0}});
    map<int, int> id_to_col;
    id_to_col[4] = 0;
    id_to_col[3] = 1;

    REQUIRE_THROWS(PageRank(weights, id_to_col));
}

TEST_CASE("Too long column name map") {
    vector<vector<float>> weights({{0.4, 0.3, 0.1}, {0.2, 0.5, 0.8}, {0.4, 0.2, 0}});
    map<int, int> id_to_col;
    id_to_col[4] = 0;
    id_to_col[3] = 1;
    id_to_col[5] = 2;
    id_to_col[0] = 3;

    REQUIRE_THROWS(PageRank(weights, id_to_col));
}
