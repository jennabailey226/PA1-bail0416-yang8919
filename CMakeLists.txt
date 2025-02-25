
# Modified from thrift tutorial

## TO BUILD:
## Create a /build directory - mkdir build
## cd into build - cd build
## call cmake - cmake ..
## call make - make

cmake_minimum_required(VERSION 3.28)
project(thrfit_distributedML)

# Make sure gen-cpp files can be included
include_directories("${CMAKE_CURRENT_BINARY_DIR}")
include_directories("${CMAKE_CURRENT_BINARY_DIR}/gen-cpp")

# CHANGEME set thrift include
# Use $ENV{HOME} to start the filepath from your home directory
# include the directory /thrift-0.19.0/lib/cpp/src
include_directories("$ENV{HOME}/thrift-0.19.0/lib/cpp/src")

# need to include each individual cpp file from the gen-cpp folder
set(exgencpp_SOURCES
    gen-cpp/Coordinator.cpp
    gen-cpp/ComputeNode.cpp
    gen-cpp/distributedML_types.cpp
)
add_library(exgencpp STATIC ${exgencpp_SOURCES})

set(ml_SOURCES ML/ML/ML.cpp)
add_library(ml STATIC ${ml_SOURCES})

# Compile server executable
add_executable(coordinator Coordinator_server.cpp)
add_executable(computeNode ComputeNode_server.cpp)
target_link_libraries(coordinator exgencpp)
target_link_libraries(coordinator ml)
target_link_libraries(computeNode exgencpp)
target_link_libraries(computeNode ml)


# CHANGEME set thrift library location, link to `libthrift.so` or `libthrift.a`
# The library can be found at your thrift install location: /thrift-0.19.0/lib/cpp/.libs/libthrift.so
target_link_libraries(coordinator "$ENV{HOME}/thrift-0.19.0/lib/cpp/.libs/libthrift.so")
target_link_libraries(computeNode "$ENV{HOME}/thrift-0.19.0/lib/cpp/.libs/libthrift.so")

# target_link_libraries(exServer thrift)  # does NOT work on CSElabs, must link to library location
