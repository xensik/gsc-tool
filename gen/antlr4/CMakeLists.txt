cmake_minimum_required(VERSION 3.10)
project(ANTLR4Project)

# Set C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include ANTLR4 runtime
include_directories(${CMAKE_SOURCE_DIR}/runtime/runtime/src)

# Add ANTLR4 runtime source files
file(GLOB_RECURSE ANTLR4_RUNTIME_SRC "${CMAKE_SOURCE_DIR}/runtime/runtime/src/*.cpp")

# Add your source files
set(SOURCE_FILES main.cpp)

# Add generated ANTLR4 files
file(GLOB GENERATED_SRC "${CMAKE_SOURCE_DIR}/generated/*.cpp")
include_directories(${CMAKE_SOURCE_DIR}/generated)

# Include nlohmann/json library
include_directories(${CMAKE_SOURCE_DIR}/nlohmann)

# Create the executable
add_executable(ANTLR4Project ${SOURCE_FILES} ${ANTLR4_RUNTIME_SRC} ${GENERATED_SRC})

# Link libraries if needed (e.g., pthread)
target_link_libraries(ANTLR4Project pthread)