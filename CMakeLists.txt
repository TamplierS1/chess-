cmake_minimum_required(VERSION 3.17.0)
project(chess++)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

add_executable(chess++ "")
add_subdirectory(src)
add_subdirectory(third_party/raylib)

set(CXX_COMPILE_FLAGS)
set(CXX_LINK_FLAGS)
list(APPEND CXX_COMPILE_FLAGS -std=c++20 -Wall -Wextra -pedantic -Wno-narrowing -Wno-sign-compare
        -Wno-missing-field-initializers)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    list(APPEND CXX_COMPILE_FLAGS -fno-omit-frame-pointer
            -fno-optimize-sibling-calls)
    list(APPEND CXX_LINK_FLAGS
            -fno-omit-frame-pointer -fno-optimize-sibling-calls)
elseif (CMAKE_BUILD_TYPE MATCHES Release)
    list(APPEND CXX_COMPILE_FLAGS -O3)
endif ()

set(CXX_INCLUDE_DIRS)
set(CXX_LINK_LIBS)
list(APPEND CXX_INCLUDE_DIRS
    "include"
    "third_party/raylib/src")

list(APPEND CXX_LINK_LIBS raylib stdc++fs)

target_compile_options(chess++ PRIVATE ${CXX_COMPILE_FLAGS})
target_include_directories(chess++ PRIVATE SYSTEM
        ${CXX_INCLUDE_DIRS})
target_link_libraries(chess++ ${CXX_LINK_LIBS})
