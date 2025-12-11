#pragma once

#ifndef TERMINAL_LIBRARY_BASE_
#define TERMINAL_LIBRARY_BASE_

namespace terminal {

// Clear screen
void cls();

// Erase backward characters
void BackSpace();
void BackSpace(const int &count);

// Reset cursor & clear screen
void init_cursor();

// Move cursor to row/col
void up_for(const int &num);
void down_for(const int &num);
void l_for(const int &num);
void r_for(const int &num);
void up_to_bol(const int &num);
void down_to_bol(const int &num);
void l_to(const int &num);

void move_to(const int &row, const int &col);

// Terminal size
int get_terminal_columns();
int get_terminal_rows();

// Get current cursor position (row, col)
void get_cursor_position(int &row, int &col);

// scroll
void up_scroll(const int &num);
void down_scroll(const int &num);

// print
void print_bold(const char *str);
void print_thick(const char *str);
void print_italic(const char *str);
void print_under_line(const char *str);
void print_blink(const char *str);
void print_fast_blink(const char *str);
void print_reverse(const char *str);
void print_hide(const char *str);
void print_cancel(const char *str);

} // namespace terminal

#endif // TERMINAL_LIBRARY_BASE_
