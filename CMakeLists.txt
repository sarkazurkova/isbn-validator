cmake_minimum_required(VERSION 3.20)
project(isbn)

set(CMAKE_CXX_STANDARD 17)

add_executable(isbn main.cpp
        Kniha.h
        Kniha.cpp
)
