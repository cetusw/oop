cmake_minimum_required(VERSION 3.30)
project(MyArray)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest REQUIRED)

add_executable(MyArray main.cpp
        MyArray.h)

add_executable(my-array-tests
        Test/MyArrayTest.cpp
)

target_link_libraries(my-array-tests
        PRIVATE
        GTest::GTest
        GTest::Main
)

target_include_directories(my-array-tests
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
