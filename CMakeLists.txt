cmake_minimum_required(VERSION 3.20)
project(Airline_System)

set(CMAKE_CXX_STANDARD 14)

if(CMAKE_BUILD_TYPE AND (CMAKE_BUILD_TYPE STREQUAL "Release"))
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
endif()
add_executable(Airline_System main.cpp Airline.cpp PriorityList.cpp QueueList.cpp utils.cpp "Vector.hpp"
        "test.hpp" "Queue.cpp")
