cmake_minimum_required(VERSION 3.15)
project(sf_bridge)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -DNDEBUG -march=native -Wall -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DUSE_AVX2 -DUSE_POPCNT")

set(SF_SRC "/home/sid/Documents/GitHub/Stockfish/src")

include_directories(${SF_SRC})

file(GLOB SF_CPP 
    "${SF_SRC}/*.cpp" 
    "${SF_SRC}/nnue/*.cpp"
    "${SF_SRC}/nnue/features/*.cpp"
    "${SF_SRC}/syzygy/*.cpp"
)
list(REMOVE_ITEM SF_CPP "${SF_SRC}/main.cpp")

add_library(sf_bridge STATIC sf_bridge.cpp ${SF_CPP})
if(UNIX)
    target_link_libraries(sf_bridge pthread)
endif()
