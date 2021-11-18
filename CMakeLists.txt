cmake_minimum_required(VERSION 3.20)
project(Airline_System)

set(CMAKE_CXX_STANDARD 14)

add_executable(Airline_System main.cpp Airline.cpp PriorityList.cpp QueueList.cpp utils.cpp)
