cmake_minimum_required(VERSION 3.30)
project(Date)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest REQUIRED)

add_executable(Date main.cpp
        Date.cpp
        Date.h
        Month.h
        WeekDay.h)

add_executable(date-tests
        Date.cpp
        Date.h
        Month.h
        WeekDay.h
        Test/DateTest.cpp
)

target_link_libraries(date-tests
        PRIVATE
        GTest::GTest
        GTest::Main
)

target_include_directories(date-tests
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
