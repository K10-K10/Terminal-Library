# utils documents

This module provides various utility functions for the Terminal Library, including color management and other helpful tools for building text-based user interfaces.

These functions are part of the `terminal::utils` namespace.

Terminal top-left corner is considered as (0, 0) position.

## General

- `void clear()`: Clears the terminal screen.

- `void backSpace(int = 1)`: erase the specified number of characters backward from the current cursor position.

- `void initCursor()`: Initializes the terminal cursor position.
## cursor Management
- `std::pair<int, int> getCursorPosition()`: Returns the current cursor position as a pair of integers (row, column).
- `void upFor(int)`: Moves the cursor up by the specified number of lines.
- `void downFor(int)`: Moves the cursor down by the specified number of lines.
- `void rightFor(int)`: Moves the cursor right by the specified number of columns.
- `void leftFor(int)`: Moves the cursor left by the specified number of columns.
- `void moveTo(int row, int col)`: Moves the cursor to the specified (row, col) position.
- `void upForBeginOfLine(int)`: Moves the cursor up by the specified number of lines and to the beginning of the line.
- `void downForBeginOfLine(int)`: Moves the cursor down by the specified number of lines and to the beginning of the line.
- `void lTo(int)`: Moves the cursor to the specified column in the current row.

## Color Management
