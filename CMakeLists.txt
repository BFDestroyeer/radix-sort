cmake_minimum_required(VERSION 2.8)

project(radix-sort)

include_directories(include)

set(RADIX_SORT_SOURCE
    src/sort.cpp
    src/main.cpp
)

add_executable(radix-sort ${RADIX_SORT_SOURCE})