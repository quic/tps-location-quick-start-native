cmake_minimum_required(VERSION 3.0.0)
project(location-quick-start)

include_directories(lib)
link_directories(lib)

add_executable(location-quick-start location-quick-start.cpp)
target_link_libraries(location-quick-start wpsapi)
