cmake_minimum_required(VERSION 3.26)
project(iv C CXX)

find_package(SDL3 REQUIRED)

add_executable(iv)

target_sources(iv
PRIVATE
    iv.c
)

target_link_libraries(iv SDL3::SDL3)