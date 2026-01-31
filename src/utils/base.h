#pragma once

#ifndef TERMINAL_LIBRARY_UTILS_BASE_H_
#define TERMINAL_LIBRARY_UTILS_BASE_H_

#include <utility>

#define FULL -1

namespace terminal {
namespace utils {

// Clear screen
void clear();

// Erase backward characters
void backSpace();
void backSpace(const int& count);

// Reset cursor & clear screen
void initCursor();

// Move cursor to row/col
void UpFor(const int& num);
void downFor(const int& num);
void lFor(const int& num);
void rFor(const int& num);
void upForBeginOfLine(const int& num);
void downForBeginOfLine(const int& num);
void lTo(const int& num);

void moveTo(const int& row, const int& col);

// Terminal size
int getTerminalColumns();
int getTerminalRows();

// Get current cursor position (row, col)
std::pair<int, int> getCursorPosition();

// scroll
void upScroll(const int& num);
void downScroll(const int& num);

// print
void printBold(const char* str);
void printThick(const char* str);
void printItalic(const char* str);
void printUnderline(const char* str);
void printBlink(const char* str);
void printFastBlink(const char* str);
void printReverse(const char* str);
void printHide(const char* str);
void printCancel(const char* str);
}  // namespace utils
}  // namespace terminal

#endif  // TERMINAL_LIBRARY_UTILS_BASE_H_
