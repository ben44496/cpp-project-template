<!-- In addition to the code itself, you must include a human-readable README which describes: (1) The location of all major code, data, and results. (2) Full instructions on how to build and run your executable, including how to define the input data and output location for each method. (3) Full instructions how to build and run your test suite, including a general description on what tests you have created. It is in your best interest to make the instructions (and the running of your executables and tests) as simple and straightforward as possible. -->


# Railroads in the US
##### Project Members: 
- Benjamin Nguyen
- Laney Moy
- Tarun Voruganti
- Parth Saxena

##### Project Description
Being captivated by Thomas the Tank Engine (and his variants) in our childhoods, we decided to remember him by parsing and traversing a graph of railroad stations and routes in the continental United States. With over a couple hundred thousand nodes, and way more edges, our graph will be sure to amaze you. 

We wanted to accurately chart out railroads in the continental United States to better provide a framework of traversing a weighted graph to help understand our nation's railroad structure. Our codebase so far only supports parsing the traversing the Railroad Dataset, but it could definitely be generalized to weighted graphs in general. Being able to understand pathing and ranking of railroads are paramount to the infrastructure of our nation, and in this codebase we try to give a more thorough picture of the situation by parsing thousands of railroad stations and routes.

We decided to use the dataset from (Amtrak)[https://data.world/albert/amtrak/workspace/file?filename=Amtrak_Routes.geojson] as they are one of the most thorough datasets being supported by the government through the DOT. We decided to use the connected component with the most nodes in our graph to simulate the system and drop any malformed data or incomplete records.

We implement 2 graph algorithms and one traversal. Our graph algorithms are A-Star and PageRank and also a BFS traversal for this dataset. The A* heuristic will help find the shortest path between two railroad stations and our PageRank algorithm will find the railroad stations with the most traffice.

We hope you enjoy our project!

# Project Structure
The project structure is created to maximize modularity, increase compartmentalization, and make use of tools through CMake. Each sub-project of the overall project has its own folder, wherein each contains its own test, main methods, CMake files, and header files, thus increasing modularity of the overall project. Thus, each sub-project can actually stand alone on its own, and we add them here together much like applications rather than a hard-stuck part of the project. An example project structure is shown below for better visualization of the structure:
```
project/
> parsing/
    > include/
        - ...header files
    > src/
        - ...src files
    - main.cpp
    - CMakeLists.txt
> bfs/
    |-- ...
```

This is a very similar structure as all other large open-source code bases like OpenCV as it allows maximum modularity and stand-alone applications. 

# First Time
We will refer to the home project directory as `project/`, but it could be in your `cs225` folder with an absolute path that could look like `/usr/thomas3/cs225/project` or `~/cs225/project` as an example (here, our actualy project name is `tvorug2-elenam3-bnguyen4-parths3`). If this is your first time with the project and you are unfamiliar with the running scripts, then please execute the following in your command line (Note you must type in the stuff after the dollar sign. The stuff before the `$` symbol denotes the current filepath):

`$ cd project/`
`project$ chmod +x run.sh`
`project$ ./run.sh`

This will run the included script that runs the main method with default arguments and also all tests in each subdirectory. This is just a concatenation of running the bake, tests, and main at once.

# Building Files
We decided to use CMake in this project due to its usefulness in helping us create Makefiles through a list of well-defined macros. The following command will bake the project (Build & Make). Run these in your local terminal. Note, please consider doing all of this on EWS as we assume tools on EWS (like CMake3 etc.).

`project$ ./bake.sh`

# Running Main, Tests
### Main
To run main or tests, you can just execute the main script like so:
`project$ ./main.sh`

The main method also includes some additional input if you would like to play around with the inputs. You can run `./main -h` or `./main --help` for more information on the usage type. The result should print something like:

`Usage: ./main [nodes file] [edges file]`

For example, we provided a fake dataset so you could run the following:

`./main ../data/nodes.csv ../data/edges.csv`

Note that everything will be relative to the `src/` directory even though the script is in the `project/` directory.

### Tests
I have made a `test.sh` script that runs all the tests in the subdirectories. You can just run it like so:

`project$ ./test.sh`

and you should see the success on all 4 parts.

##### Test Suite

For **BFS** testing, for some of the test cases we looked at how our coded was assessed for MP Traversals since that involved a BFS search. We replicated their ordering test cases for our BFS traversal. Other than that we tested that the correct size was found for the first connected component in our dataset. We also ensured that a cycle in nodes would not run endlessly. We also ensured that our `pop` and `peek` methods worked appropriately and did not manipulate the nodes in the traversal in unintended ways. We also made test cases involving graphs with single nodes to ensure that the BFS traversal worked for edge cases/situations. Lastly we also tested that our BFS traversal would be empty after visiting all nodes in the traversal, and wouldn't be empty after visiting only some nodes in the traversal. 

To test **parsing**, we tested both the `CSVParser` as well as the internal `Node` class. For testing the `CSVParser` we ensured that the size of the nodes vector was accurate after parsing the inputted data. We tested that the first, last, and middle nodes were accurate to ensure the ordering of the dataset was maintained in the internal `Node`s `vector`. We then also had to test that `Edge`s were parsed correctly. We ensured that a parsed `Edge` had the correct `fromNode` and `toNode` ID as well as the correct `weight` (distance of the route) edge. Lastly, we tested that the `rows()` method worked accurately and ensured that an empty dataset did not cause problems.  

To test the **PageRank** algorithm, we tested the PageRank object constructor and its solve method, which runs the algorithm. We checked that the constructor throws exceptions for non-square weights matrix dimensions and for column name maps of the incorrect length. We tested the solve method for correctness on small and large matrices and also checked edge cases. We tested matrices with one zero column and with multiple zero columns, as well as matrices with a column or multiple columns summing to more than 1. These cases ensured that we properly converted the weights matrix into a Markov matrix before running power iteration.

To test the **A\*** algorithm, we tested the A* object constructor and its solve method, which runs the algorithm. We checked that the constructor throws exceptions for railroad ID's that do not exist. We tested the solve method for correctness on small graphs. First, we made sure that it found the correct path between a few nodes in a straight line and only 1 path. Then we tested a more complex graph with multiple paths and different weights and the algorithm successfully found the shortest path. These cases ensured that A* correctly analyzed the graph and found the shortest path between 2 paths.

# Presentation

Presentation Link:
https://drive.google.com/file/d/1sV3BZmFld6N057eLbDqxRHl1wUO21Oml/view?usp=sharing

Slides:
https://drive.google.com/file/d/1sV3BZmFld6N057eLbDqxRHl1wUO21Oml/view?usp=sharing

