#pragma once

#ifndef TERMINAL_LIBRARY_UTILS_BASE_H_
#define TERMINAL_LIBRARY_UTILS_BASE_H_

namespace terminal {
namespace utils {
// Clear screen
void clear();

// Erase backward characters
void BackSpace();
void BackSpace(const int& count);

// Reset cursor & clear screen
void InitCursor();

// Move cursor to row/col
void UpFor(const int& num);
void DownFor(const int& num);
void LFor(const int& num);
void RFor(const int& num);
void UpForBeginOfLine(const int& num);
void DownForBeginOfLine(const int& num);
void LTo(const int& num);

void MoveTo(const int& row, const int& col);

// Terminal size
int GetTerminalColumns();
int GetTerminalRows();

// Get current cursor position (row, col)
void GetCursorPosition(int& row, int& col);

// scroll
void UpScroll(const int& num);
void DownScroll(const int& num);

// print
void print_bold(const char* str);
void print_thick(const char* str);
void print_italic(const char* str);
void print_under_line(const char* str);
void print_blink(const char* str);
void print_fast_blink(const char* str);
void print_reverse(const char* str);
void print_hide(const char* str);
void print_cancel(const char* str);
}  // namespace utils
}  // namespace terminal

#endif  // TERMINAL_LIBRARY_UTILS_BASE_H_
