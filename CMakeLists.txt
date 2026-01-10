cmake_minimum_required(VERSION 3.16)
project(terminalLib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE LIB_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.cc"
)

target_include_directories(terminal PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_executable(test
    test/main.cpp
)

target_link_libraries(test PRIVATE terminalLib)

add_executable(test
    test/main.cpp
)

target_link_libraries(test PRIVATE terminal)
