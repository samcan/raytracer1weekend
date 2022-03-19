cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 17)


project(raytracer1weekend VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(raytrace ./src/raytrace.cpp)