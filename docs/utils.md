# utils documents

This module provides various utility functions for the Terminal Library, including color management and other helpful tools for building text-based user interfaces.

These functions are part of the `terminal::utils` namespace.

Terminal top-left corner is considered as (0, 0) position.

## General

- `void clear()`: Clears the terminal screen.

- `void backSpace(int = 1)`: erase the specified number of characters backward from the current cursor position.

- `void initCursor()`: Initializes the terminal cursor position.

- `std::pair<int, int> getTerminalSize()`: Returns the current size of the terminal as a pair of integers (rows, columns).

## Print Management

- `void printBold(const char* str)`: Prints the given string in bold text.

- `void printThick(const char* str)`: Prints the given string in thick text.

- `void printItalic(const char* str)`: Prints the given string in italic text.

- `void printUnderlined(const char* str)`: Prints the given string with an underline.

- `void printBlink(const char* str)`: Prints the given string with a blinking effect.

- `void printFastBlink(const char* str)`: Prints the given string with a fast blinking effect.

- `void printReverse(const char* str)`: Prints the given string with reversed foreground and background colors.

- `void printHide(const char* str)`: Prints the given string as hidden text.

- `void printCancel(const char* str)`: Prints the given string with all text attributes canceled.

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

- `void upScroll(int)`: Scrolls the terminal content up by the specified number of lines.

- `void downScroll(int)`: Scrolls the terminal content down by the specified number of lines.

## Color Management

### Colour Macros

- `text_black`, `text_red`, `text_green`, `text_yellow`, `text_blue`, `text_magenta`, `text_cyan`: Sets the text color to the specified color.

- `fill_black`, `fill_red`, `fill_green`, `fill_yellow`, `fill_blue`, `fill_magenta`, `fill_cyan`: Sets the background fill color to the specified color.

## Print Functions with Color

- `void printColor(int txt_color, const char* str)`: Prints the given string with the specified text color.

- `void printColor(int txt_color, int fill_color, const char* str)`: Prints the given string with the specified text and background fill colors.
