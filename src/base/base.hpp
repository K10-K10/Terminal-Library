#pragma once

#ifndef TERMINAL_LIBRARY_BASE_
#define TERMINAL_LIBRARY_BASE_

#include <cstdlib>
#include <iostream>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>

namespace T_base {

inline void cls() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

inline void BackSpace(int letter_num) {
  for (int i = 0; i < letter_num; i++) {
    std::cout << "\x08 \x08" << std::flush;
  }
}

inline void init_cursor() { std::cout << "\x1b[2J\x1b[H" << std::flush; }

inline void move_cursor(int x, int h) {
  std::cout << "\033[" << x << ";" << h << "H" << std::flush;
}

inline int get_terminal_columns() {
  struct winsize w;
  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) != -1)
    return w.ws_col;
  else
    return -1;
}

inline int get_terminal_rows() {
  struct winsize w;
  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) != -1)
    return w.ws_row;
  else
    return -1;
}

} // namespace T_base

#endif // TERMINAL_LIBRARY_BASE_
