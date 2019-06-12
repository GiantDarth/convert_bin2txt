cmake_minimum_required(VERSION 3.10)
project(convert_bin2txt)

set(CMAKE_CXX_STANDARD 17)

add_executable(convert_bin2txt main.cpp)

find_package(Boost REQUIRED)

target_link_libraries(convert_bin2txt Boost::boost)