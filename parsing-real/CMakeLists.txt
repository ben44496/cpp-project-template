cmake_minimum_required(VERSION 3.1)

add_compile_options(-std=c++11)

# Add header files
file(GLOB INCLUDES "includes/*.h")

# Add src files
file(GLOB SOURCES "src/*.cpp")

# Add testing sources
file(GLOB TEST_SOURCES "tests/*.cpp")

# Add library interface for our files
add_library(ParsingLib ${SOURCES} ${INCLUDES})

# Link
target_include_directories(ParsingLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Add the executable
add_executable(main-parsing main.cpp)
target_link_libraries(main-parsing ParsingLib)

target_include_directories(main-parsing PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


# Add Catch2
Include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v2.13.1
)

FetchContent_MakeAvailable(Catch2)
add_executable(test-parsing ${TEST_SOURCES})
target_link_libraries(test-parsing ParsingLib)
# target_link_libraries(test-parsing PRIVATE Catch2::Catch2)