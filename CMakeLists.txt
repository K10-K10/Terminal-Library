cmake_minimum_required(VERSION 3.12)
project(TerminalLib VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# include/
# ├── terminal.hpp
# └── terminal/xxx.hpp
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB TERMINAL_SRC
    src/*.cpp
)

add_library(terminal STATIC
    ${TERMINAL_SRC}
)

target_include_directories(terminal
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
install(TARGETS terminal
    ARCHIVE DESTINATION lib
)

install(DIRECTORY include/ DESTINATION include)

include(CPack)
set(CPACK_PACKAGE_NAME "TerminalLib")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
