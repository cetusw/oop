cmake_minimum_required(VERSION 3.30)
project(vector_1)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.4.0
)
FetchContent_MakeAvailable(Catch2)

add_executable(vector Vector.cpp main.cpp)
add_executable(vector-tests Vector.cpp tests/VectorTests.cpp)

target_link_libraries(vector-tests PRIVATE Catch2::Catch2WithMain)
