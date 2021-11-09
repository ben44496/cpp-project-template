cmake_minimum_required(VERSION 2.8)

# Set the project name
# project(Parsing)

# Specify the C++ standard (CMake3+)
# set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_EXTENSION OFF)
add_compile_options(-std=c++11) # CMake 2.8.12 or newer

# Add header files
# could do something like: set(SOURCES src/node.cpp src/parser.cpp etc.)
file(GLOB INCLUDES "include/*.h") # We do it this way because it allows us to use wildcard

# Add src files
file(GLOB SOURCES "src/*.cpp")

# Add testing sources
file(GLOB TEST_SOURCES "tests/*.cpp")

# Add library interface for our files
add_library(ParsingLib ${SOURCES} ${INCLUDES})

# Link
target_include_directories(ParsingLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# add the executable
add_executable(main-parsing main.cpp)
target_link_libraries(main-parsing ParsingLib)
# add_executable(test ${TEST_SOURCES} ${SOURCES} ${INCLUDES})


target_include_directories(main-parsing PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
# target_include_directories(test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# # i'm not too sure why I need to add it but the github said to
# include(CTest)
# include(ParseAndAddCatchTests)
# ParseAndAddCatchTests(test)

# Add Catch2
Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v2.13.1)

FetchContent_MakeAvailable(Catch2)
add_executable(test-parsing ${TEST_SOURCES})
target_link_libraries(test-parsing ParsingLib)
target_link_libraries(test-parsing PRIVATE Catch2::Catch2)