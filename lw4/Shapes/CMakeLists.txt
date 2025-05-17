cmake_minimum_required(VERSION 3.30)
project(Shapes)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest REQUIRED)
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

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
        Size.h
        Interface/ICanvas.h
        Interface/ICanvasDrawable.h
        Canvas/Canvas.cpp
        Canvas/Canvas.h
)

add_executable(shapes-tests
        Test/ShapesTest.cpp
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
        Size.h
        Test/ShapeControllerTest.cpp
)

target_link_libraries(Shapes
        sfml-graphics
        sfml-window
        sfml-system
)

target_link_libraries(shapes-tests
        PRIVATE
        GTest::GTest
        GTest::Main
)

target_include_directories(shapes-tests
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
