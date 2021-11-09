# Project Proposal

1. *Leading Question* Given a dataset of railroad stations and paths between them, find routes between stations and evaluate station usage.

2. *Data Acquisition and Processing* We propose using the Amtrak railroad stations and routes (datasets)[https://data.world/albert/amtrak/workspace/file?filename=Amtrak_Routes.geojson]. The data is in a GeoJSON, which we can parse using this reference from (Stack Overflow)[https://stackoverflow.com/questions/32205981/reading-json-files-in-c]. We propose to use a node to represent a railroad station with weighted edges to indicate the distance between stations. We will drop any malformed data or incomplete records.

3. *Graph Algorithms* For our graph traversal, we propose to implement a simple BFS using a iterator. The iterator constructor expects an input of the starting course number and whether to traverse prerequisites. Upon every call of `operator++` on the iterator, we expect it to update to another node until there are no further nodes to traverse.

For one of our algorithms, we will conduct an A* routine to find the shortest path between two railroad stations. 

For our final algorithm, we will use the PageRank algorithm to rank stations based on expected usage.

4. *Timeline*

April 8 - Meet to complete team contract and project proposal

April 9 - Submit team contract and project proposal

April 11 - Set up initial repository and Makefile

April 15 - Read data into graph and pass simple tests

April 19 - Write BFS iterator and pass simple tests

April 23 - Write A* algorithm 

May 1 - Write PageRank algorithm

May 5 - Finish report

May 8 - Meet to record final presentation

May 12 - Finish editing presentation and submit
