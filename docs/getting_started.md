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

# How to use
## Terminal Initialization
Before using any terminal functionalities, you need to initialize the terminal.

```cpp
terminal::Terminal.init();
```

`Terminal.init()` sets up the terminal for TUI operations, enabling features like color support and cursor management.[see Terminal Documentation](terminal.md)

## Create Objects

To create and manipulate terminal objects, you can use the `terminal::Object` class. Here's a simple example of how to create an object and display it in the terminal:

```cpp
terminal::Object myObject("Title", "This is the content of the object.", 5, 10, 10, 30, 1);
myObject.show();
```

This code creates a terminal object with a title, content, position, size, and border style, and then displays it in the terminal.[see Object Documentation](objects.md)

## Exit Terminal
When you are done with your TUI application, make sure to properly exit the terminal mode to restore the terminal to its original state.
```cpp
terminal::Terminal.exit();
```

# Examples
```cpp
#include "terminal/Terminal.h"

int main() {
  terminal::Terminal.init();
  terminal::Object myObject("Welcome", "Hello, Terminal Library!", 5, 10, 10, 40, 1);
  myObject.show();
  terminal::Terminal.exit();
  return 0;
}
```
