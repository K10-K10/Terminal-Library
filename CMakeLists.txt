cmake_minimum_required(VERSION 3.16)
project(terminal LANGUAGES CXX)

add_library(terminal
    src/feat/feature.cc
    src/field/field.cc
    src/input/cursor.cc
    src/input/keyboard.cc
    src/obj/obj.cc
    src/obj/manager.cc
    src/obj/render.cc
    src/utils/base.cc
    src/utils/color.cc
    src/terminal/Terminal.cc
)

target_include_directories(terminal PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_features(terminal PUBLIC cxx_std_20)

option(TERMINAL_BUILD_TESTS "Build dev tests" OFF)

if (TERMINAL_BUILD_TESTS AND NOT TARGET terminal_test)
  add_executable(terminal_test test/main.cpp)
  target_link_libraries(terminal_test PRIVATE terminal)
endif()
