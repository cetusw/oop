cmake_minimum_required(VERSION 3.30)
project(Dictionary)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.4.0
)
FetchContent_MakeAvailable(Catch2)

add_executable(Dictionary Dictionary.cpp main.cpp)
add_executable(dictionary-tests Dictionary.cpp Test/DictionaryTest.cpp)

target_link_libraries(dictionary-tests PRIVATE Catch2::Catch2WithMain)

