cmake_minimum_required(VERSION 3.16)
project(terminalLib)

set(CMAKE_CXX_STANDARD 20)

# ----------------------------------------
# Library: build from src/
# ----------------------------------------
file(GLOB_RECURSE LIB_SOURCES
    "${PROJECT_SOURCE_DIR}/src/obj/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/utils/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/func/*.cpp"
)

add_library(terminalLib ${LIB_SOURCES})

# Include the src directory so headers like "utils/base.hpp" work
target_include_directories(terminalLib PUBLIC
    "${PROJECT_SOURCE_DIR}/src"
)

# ----------------------------------------
# Test executable
# ----------------------------------------
add_executable(testRunner
    test/main.cpp
)

target_include_directories(testRunner PUBLIC
    "${PROJECT_SOURCE_DIR}/src"
)

target_link_libraries(testRunner PRIVATE terminalLib)
