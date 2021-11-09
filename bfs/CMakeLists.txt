cmake_minimum_required(VERSION 2.8)

if(POLICY CMP0015)
  cmake_policy(SET CMP0015 NEW)
endif()

# project(BFS)

# set(CMAKE_BUILD_TYPE Debug)

add_compile_options(-std=c++11)

file(GLOB INCLUDES "include/*.h")
file(GLOB SOURCES "src/*.cpp")
file(GLOB TEST_SOURCES "tests/*.cpp")

add_library(BFSLib ${SOURCES} ${INCLUDES})

target_include_directories(BFSLib PUBLIC "./include" "../parsing/include")

link_directories("../parsing")
target_link_libraries(BFSLib ParsingLib)

add_executable(main-bfs main.cpp)
add_executable(test-bfs ${TEST_SOURCES})

target_link_libraries(main-bfs BFSLib ParsingLib)

# Add Catch2
Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v2.13.1)

FetchContent_MakeAvailable(Catch2)

target_link_libraries(test-bfs PRIVATE Catch2::Catch2 BFSLib)
