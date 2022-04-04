cmake_minimum_required(VERSION 3.20)
project(Airline_System)

set(CMAKE_CXX_STANDARD 14)

if(CMAKE_BUILD_TYPE AND (CMAKE_BUILD_TYPE STREQUAL "Release"))
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
    if (NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
    endif()
endif ()

include_directories(Airline_System include/)
add_executable(Airline_System src/main.cpp src/Airline.cpp src/PriorityList.cpp 
    src/QueueList.cpp src/utils.cpp src/Queue.cpp)
