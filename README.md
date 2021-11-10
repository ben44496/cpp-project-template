# C++ Project Template
Generic C++ modular template for projects.

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
We will refer to the home project directory as `project/`. If this is your first time with the project and you are unfamiliar with the running scripts, then please execute the following in your command line (Note you must type in the stuff after the dollar sign. The stuff before the `$` symbol denotes the current filepath):

`$ cd project/`

`project$ chmod +x run.sh`

`project$ ./run.sh`

This will run the included script that runs the main method with default arguments and also all tests in each subdirectory. This is just a concatenation of running the bake, tests, and main at once.

# Building Files
We decided to use CMake in this project due to its usefulness in helping us create Makefiles through a list of well-defined macros. The following command will bake the project (Build & Make). Run these in your local terminal. Note, please consider doing all of this on EWS as we assume tools on EWS (like CMake3 etc.).

`project$ ./bake.sh`

# Running Main, Tests
## Main
To run main or tests, you can just execute the main script like so:

`project$ ./main.sh`
<!-- 
The main method also includes some additional input if you would like to play around with the inputs. You can run `./main -h` or `./main --help` for more information on the usage type. The result should print something like:

`Usage: ./main [nodes file] [edges file]`

For example, we provided a fake dataset so you could run the following:

`./main ../data/nodes.csv ../data/edges.csv` -->

Note that everything will be relative to the `src/` directory even though the script is in the `project/` directory.

## Tests
I have made a `test.sh` script that runs all the tests in the subdirectories. You can just run it like so:

`project$ ./test.sh`

and you should see the success on all parts.

