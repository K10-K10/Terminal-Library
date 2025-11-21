#pragma once

#ifndef TERMINAL_LIBRARY_BASE_
#define TERMINAL_LIBRARY_BASE_
#include <cstdlib>
#include <iostream>

namespace T_base {
void BackSpace(int letter_num) {
  for (int i = 0; i < letter_num; i++) {
    std::cout << "\x08 \x08" << std::flush;
  }
};
void cls() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

} // namespace T_base

#endif TERMINAL_LIBRARY_BASE_
