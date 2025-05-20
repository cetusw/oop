cmake_minimum_required(VERSION 3.30)
project(FindMaxEx)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest REQUIRED)

add_executable(FindMaxEx main.cpp
        FindMaxExTest.h
        Sportsman.h
)

add_executable(find-max-ex-tests
        FindMaxExTest.h
        Sportsman.h
        Test/FindMaxExTest.cpp
)

target_link_libraries(find-max-ex-tests
        PRIVATE
        GTest::GTest
        GTest::Main
)

target_include_directories(find-max-ex-tests
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)