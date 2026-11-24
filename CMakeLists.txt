cmake_minimum_required(VERSION 3.20)
project(ode_lesson CXX)
add_compile_options(-Wall -Wextra)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

find_package(Eigen3 3.3 REQUIRED NO_MODULE)

add_library(numerics ode.cpp)
target_link_libraries(numerics PUBLIC Eigen3::Eigen)

add_library(output io.cpp)
target_link_libraries(output PUBLIC numerics)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE numerics output)