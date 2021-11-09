cmake_minimum_required(VERSION 2.8)

# Specify the C++ standard (CMake3+)
add_compile_options(-std=c++11) # CMake 2.8.12 or newer

# Add header files
# could do something like: set(SOURCES src/node.cpp src/parser.cpp etc.)
file(GLOB INCLUDES "include/*.h") # We do it this way because it allows us to use wildcard

# Add src files
file(GLOB SOURCES "src/*.cpp")

# Add testing sources
file(GLOB TEST_SOURCES "tests/*.cpp")

# Add library interface for our files
add_library(AStarLib ${SOURCES} ${INCLUDES})

# Link and include dependencies
target_include_directories(AStarLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} "../parsing/include")

# Link Parsing Library to the a-star one
link_directories("../parsing")
target_link_libraries(AStarLib ParsingLib)

# add the executable
add_executable(main-astar main.cpp)
target_link_libraries(main-astar AStarLib)
# add_executable(test ${TEST_SOURCES} ${SOURCES} ${INCLUDES})


target_include_directories(main-astar PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Add Catch2
Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v2.13.1)

FetchContent_MakeAvailable(Catch2)
add_executable(test-astar ${TEST_SOURCES})
target_link_libraries(test-astar PRIVATE Catch2::Catch2 AStarLib)