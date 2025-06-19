cmake_minimum_required(VERSION 3.30)
project(HTTP)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest REQUIRED)

add_executable(HTTP main.cpp
        HttpUrl.cpp
        HttpUrl.h
        UrlParsingError.h
        Protocol.h
)

add_executable(http-url-tests
        HttpUrl.cpp
        HttpUrl.h
        UrlParsingError.h
        Protocol.h
        Test/HttpUrlTest.cpp
)

target_link_libraries(http-url-tests
        PRIVATE
        GTest::GTest
        GTest::Main
)

target_include_directories(http-url-tests
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)