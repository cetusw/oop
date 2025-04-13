cmake_minimum_required(VERSION 3.30)
project(Car)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.4.0
)
FetchContent_MakeAvailable(Catch2)

add_executable(Car Car.cpp main.cpp
        CarController.cpp)
add_executable(car-tests Car.cpp Test/CarTest.cpp)

target_link_libraries(car-tests PRIVATE Catch2::Catch2WithMain)