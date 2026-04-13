# Getting Started

This document will guide you through the process of setting up and using the TUI library in your C++ projects. Follow the steps below to get started.

## Installation
1. Clone the repository:
    ```bash
    git clone https://github.com/K10-K10/Terminal-Library.git
    ```

1. Link the library to your `CMakeLists.txt`:
    ```cmake
    add_subdirectory(path/to/Terminal-Library)
    ```

## Usage

This library is header-only, so you can directly include the header files in your project.

```cpp
#include <terminal.h>
```

## How to Use

First, initialize the terminal:

```cpp
app.init();
```

Then, you can create and manipulate terminal elements as needed. For example, to create a simple text element:

```cpp
terminal::Text text("Hello, World!");
```

Finally, draw the terminal to see the changes:

```cpp
app.loop{[&](){ app.draw(); }};
```

When you're done, make sure to clean up resources:

```cpp
app.stop();
```

example code can be found in the [Examples](docs/examples.md) section of the documentation.

author: K10-K10
update: 12/04/2026
