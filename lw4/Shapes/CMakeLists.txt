cmake_minimum_required(VERSION 3.30)
project(Shapes)

set(CMAKE_CXX_STANDARD 20)

add_executable(Shapes main.cpp
        Point.h
        Interface/IShape.h
        Shape/LineSegment.cpp
        Shape/LineSegment.h
        Interface/ISolidShape.h
        Shape/Triangle.cpp
        Shape/Triangle.h
        Shape/Rectangle.cpp
        Shape/Rectangle.h
        Shape/Circle.cpp
        Shape/Circle.h
        Controller/ShapeController.cpp
        Controller/ShapeController.h
        Shape/Shape.cpp
        Shape/Shape.h
        Shape/SolidShape.cpp
        Shape/SolidShape.h
        Size.h)
