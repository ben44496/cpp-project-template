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
add_library(PageRankLib ${SOURCES} ${INCLUDES})

link_directories("../parsing")
target_link_libraries(PageRankLib ParsingLib)

# Link
target_include_directories(PageRankLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} "../parsing/include")

# add the executable
add_executable(main-pagerank main.cpp)
target_link_libraries(main-pagerank PageRankLib)

target_include_directories(main-pagerank PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Add Catch2
Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v2.13.1)

FetchContent_MakeAvailable(Catch2)
add_executable(test-pagerank ${TEST_SOURCES})
target_link_libraries(test-pagerank PRIVATE Catch2::Catch2 PageRankLib)