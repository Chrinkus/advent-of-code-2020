cmake_minimum_required(VERSION 3.16)

project(aoc_2020 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

include_directories(include)

add_subdirectory(src)
add_subdirectory(alt)