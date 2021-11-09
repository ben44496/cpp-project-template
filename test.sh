#!/bin/bash

# This is a shell script to run all tests sequentially.

TEST_PARSING="test-parsing"
TEST_BFS="test-bfs"
TEST_ASTAR="test-astar"
TEST_PAGERANK="test-pagerank"

echo "Testing Parsing"
cd parsing/
./$TEST_PARSING
cd ..

echo "Testing BFS"
cd bfs/
./$TEST_BFS
cd ..

echo "Testing A-star"
cd a_star/
./$TEST_ASTAR
cd ..

echo "Testing PageRank"
cd pagerank/
./$TEST_PAGERANK
cd ..