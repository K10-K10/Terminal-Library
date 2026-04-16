cmake_minimum_required(VERSION 3.16)
project(terminal LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(Curses REQUIRED)

add_library(terminal
    src/feat/feature.cc
    src/input/cursor.cc
    src/input/keyboard.cc
    src/utils/base.cc
    src/style/color.cc
    src/app/app.cc
    src/core/drawObj.cc
    src/core/render.cc
    src/core/screen.cc
    src/obj/block.cc
    src/obj/list.cc
    src/obj/text.cc
)

target_include_directories(terminal PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CURSES_INCLUDE_DIRS}
)

target_compile_features(terminal PUBLIC cxx_std_20)

target_link_libraries(terminal PUBLIC
    ${CURSES_LIBRARIES}
)

option(TERMINAL_BUILD_TESTS "Build dev tests" OFF)

if (TERMINAL_BUILD_TESTS AND NOT TARGET terminal_test)
  add_executable(terminal_test test/main.cpp)
  target_link_libraries(terminal_test PRIVATE terminal)
endif()
