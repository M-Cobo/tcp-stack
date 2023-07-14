cmake_minimum_required(VERSION 3.21)
project(tcp_stack)

set(CMAKE_CXX_STANDARD 20)

add_executable(tcp_stack src/main.cpp src/tuntap_if.cpp)
