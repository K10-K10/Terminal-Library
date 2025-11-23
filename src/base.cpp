#include "terminal/base.hpp"

#include <cstdlib>
#include <iostream>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

namespace terminal {

void cls() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

void BackSpace(int count) {
  if (count <= 0)
    return;

  // Move cursor left
  std::cout << "\033[" << count << "D";

  // Clear characters
  for (int i = 0; i < count; i++)
    std::cout << ' ';

  // Move back again
  std::cout << "\033[" << count << "D";
  std::cout.flush();
}

void init_cursor() { std::cout << "\x1b[2J\x1b[H" << std::flush; }

void move(int row, int col) {
  std::cout << "\033[" << row << ";" << col << "H" << std::flush;
}

int get_terminal_columns() {
  struct winsize w;
  return (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) != -1) ? w.ws_col : -1;
}

int get_terminal_rows() {
  struct winsize w;
  return (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) != -1) ? w.ws_row : -1;
}

void get_cursor_position(int &row, int &col) {
  struct termios oldt, newt;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;

  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);

  std::cout << "\033[6n" << std::flush;

  char ch;
  if (std::cin.get(ch) && ch == '\033') {
    std::cin.get(ch); // '['
    std::cin >> row;
    std::cin.get(ch); // ';'
    std::cin >> col;
    std::cin.get(ch); // 'R'
  }

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

} // namespace terminal
