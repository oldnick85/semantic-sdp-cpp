cmake_minimum_required(VERSION 3.22)
project(semantic-sdp-cpp VERSION 1.0 LANGUAGES CXX)

SET(CMAKE_CXX_FLAGS "-Wall -fno-rtti")
SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")
SET(CMAKE_CXX_FLAGS_RELEASE "-O2")
SET(CMAKE_CXX_FLAGS_DEBUG  "-O0 -g")

set(CMAKE_CXX_CPPLINT "cpplint")

add_subdirectory(src)
