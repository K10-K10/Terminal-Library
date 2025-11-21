#pragma once

#ifndef TERMINAL_LIBRARY_BASE_
#define TERMINAL_LIBRARY_BASE_

#include <cstdlib>
#include <iostream>
#include <string>

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

} // namespace T_base

#endif // TERMINAL_LIBRARY_BASE_
