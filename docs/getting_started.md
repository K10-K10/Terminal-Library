# Getting Started

## Introduction

This library is designed to help you create text-based user interfaces (TUIs) in the terminal using C++. It provides a set of tools for handling terminal input, output, colors, and cursor management.

## Setup

To get started with the Terminal Library, follow these steps:
1. **Clone the Repository**: add submodule or clone the repository to your local machine.

2. **Include the Library**: Make sure to include the necessary header files in your C++ project.

```cpp
#include "terminal/Terminal.h"
```

cmake
```
add_subdirectory($This library path$)
target_link_libraries(your_project_name terminal)
```

3. **Build Your Project**: Use CMake to configure and build your project.

> This library requires C++11 or higher.

### shortest cmake
```cmake
cmake_minimum_required(VERSION 3.16)
project(app LANGUAGES CXX)

add_subdirectory(lib/Terminal-Library)

add_executable(app src/main.cpp)
target_link_libraries(app PRIVATE terminal)
```

## namespace
All functionalities of the library are encapsulated within the `terminal` namespace.

In `terminal` namespace, you will find various modules such as `utils`, `input` that provide specific functionalities for building TUIs.
