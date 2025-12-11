#pragma once

#ifndef TERMINAL_LIBRARY_BASE_
#define TERMINAL_LIBRARY_BASE_

#include <string>

namespace terminal {

// Clear screen
void cls();

// Erase backward characters
void BackSpace(const int &count);

// Reset cursor & clear screen
void init_cursor();

// Move cursor to row/col
void move(const int &row, const int &col);

// Terminal size
int get_terminal_columns();
int get_terminal_rows();

// Get current cursor position (row, col)
void get_cursor_position(int &row, int &col);

} // namespace terminal

#endif // TERMINAL_LIBRARY_BASE_
