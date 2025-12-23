cmake_minimum_required(VERSION 3.16)
project(terminalLib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE LIB_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.cc"
)

add_library(terminalLib ${LIB_SOURCES})

target_include_directories(terminalLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_executable(testRunner
    test/main.cpp
)

target_link_libraries(testRunner PRIVATE terminalLib)
