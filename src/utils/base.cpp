#include "./base.hpp"

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

void BackSpace() {
  std::cout << "\e[1D";
  std::cout << ' ';
  std::cout << "\e[1D";
  std::cout.flush();
}

void BackSpace(int count) {
  if (count <= 0)
    return;

  // Move cursor left
  std::cout << "\e[" << count << "D";

  // Clear characters
  for (int i = 0; i < count; i++)
    std::cout << ' ';

  // Move back again
  std::cout << "\e[" << count << "D";
  std::cout.flush();
}

void init_cursor() { std::cout << "\x1b[2J\x1b[H" << std::flush; }

void up_for(const int &num) {
  if (num > 0) {
    std::cout << "\e[" << num << "A" << std::flush;
  }
}

void down_for(const int &num) {
  if (num > 0) {
    std::cout << "\e[" << num << "B" << std::flush;
  }
}

void r_for(const int &num) {
  if (num > 0) {
    std::cout << "\e[" << num << "C" << std::flush;
  }
}

void l_for(const int &num) {
  if (num > 0) {
    std::cout << "\e[" << num << "D" << std::flush;
  }
}

void up_to_bol(const int &num) {
  if (num > 0) {
    std::cout << "\e[" << num << "E" << std::flush;
  } else {
    std::cout << "\e[" << num << "F" << std::flush;
  }
}

void down_to_bol(const int &num) {
  if (num > 0) {
    std::cout << "\e[" << num << "F" << std::flush;
  } else {
    std::cout << "\e[" << num << "E" << std::flush;
  }
}

void l_to(const int &num) {
  if (num > 0) {
    std::cout << "\e[" << num << "G" << std::flush;
  }
}

void move_to(const int &row, const int &col) {
  std::cout << "\e[" << row << ";" << col << "H" << std::flush;
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

  std::cout << "\e[6n" << std::flush;

  char ch;
  if (std::cin.get(ch) && ch == '\e') {
    std::cin.get(ch); // '['
    std::cin >> row;
    std::cin.get(ch); // ';'
    std::cin >> col;
    std::cin.get(ch); // 'R'
  }

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

void up_scroll(const int &num) {
  if (num > 0) {
    std::cout << "\e[" << num << "S" << std::flush;
  } else {
    int new_n = num * -1;
    std::cout << "\e[" << num << "T" << std::flush;
  }
}

void down_scroll(const int &num) {
  if (num > 0) {
    std::cout << "\e[" << num << "T" << std::flush;
  } else {
    int new_n = num * -1;
    std::cout << "\e[" << num << "S" << std::flush;
  }
}

void print_bold(const char *str) {
  std::cout << "\e[1m" << str << "\e[0m" << std::flush;
}

void print_thick(const char *str) {
  std::cout << "\e[2m" << str << "\e[0m" << std::flush;
}

void print_italic(const char *str) {
  std::cout << "\e[3m" << str << "\e[0m" << std::flush;
}

void print_under_line(const char *str) {
  std::cout << "\e[4m" << str << "\e[0m" << std::flush;
}

void print_blink(const char *str) {
  std::cout << "\e[5m" << str << "\e[0m" << std::flush;
}

void print_fast_blink(const char *str) {
  std::cout << "\e[5m" << str << "\e[0m" << std::flush;
}

void print_reverse(const char *str) {
  std::cout << "\e[7m" << str << "\e[0m" << std::flush;
}

void print_hide(const char *str) {
  std::cout << "\e[8m" << str << "\e[0m" << std::flush;
}

void print_cancel(const char *str) {
  std::cout << "\e[9m" << str << "\e[0m" << std::flush;
}

} // namespace terminal
