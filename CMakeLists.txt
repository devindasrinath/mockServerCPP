cmake_minimum_required(VERSION 3.26)
project(mocksyncserver)

set(CMAKE_CXX_STANDARD 17)

add_executable(mocksyncserver main.cpp
        boostMocksyncServer.h)
