#pragma once

#ifndef TERMINAL_LIBRARY_BASE_
#define TERMINAL_LIBRARY_BASE_

#include <cstdlib>
#include <iostream>
#include <string>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

namespace T_base {

inline void cls() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

inline void BackSpace(int count) {
  if (count <= 0)
    return;
  std::cout << "\033[" << count << "D";
  for (int i = 0; i < count; i++)
    std::cout << ' ';
  std::cout << "\033[" << count << "D";
  std::cout.flush();
}

inline void init_cursor() { std::cout << "\x1b[2J\x1b[H" << std::flush; }

inline void move(int row, int col) {
  std::cout << "\033[" << row << ";" << col << "H" << std::flush;
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

inline void get_cursor_position(int &row, int &col) {
  termios oldt, newt;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;

  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);

  std::cout << "\033[6n" << std::flush;

  char ch;
  if (std::cin.get(ch) && ch == '\033') {
    std::cin.get(ch);
    std::cin >> row;
    std::cin.get(ch);
    std::cin >> col;
    std::cin.get(ch);
  }

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

} // namespace T_base

#endif // TERMINAL_LIBRARY_BASE_
