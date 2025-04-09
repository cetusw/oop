cmake_minimum_required(VERSION 3.30)
project(Car)

set(CMAKE_CXX_STANDARD 20)

add_executable(Car main.cpp
        Car.cpp
        Car.h
        Types.h
        CarController.cpp
        CarController.h)
