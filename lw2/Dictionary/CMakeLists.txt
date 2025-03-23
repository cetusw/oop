cmake_minimum_required(VERSION 3.30)
project(Dictionary)

set(CMAKE_CXX_STANDARD 20)

add_executable(Dictionary main.cpp
        Dictionary.cpp
        Dictionary.h
        DictionaryTypes.h)
