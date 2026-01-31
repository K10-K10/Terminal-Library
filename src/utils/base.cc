#include "utils/base.h"

#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

#include <cstdlib>
#include <iostream>

namespace terminal {
namespace utils {
void clear() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

void backSpace() {
  std::cout << "\e[1D";
  std::cout << ' ';
  std::cout << "\e[1D";
  std::cout.flush();
}

void backSpace(const int& count) {
  if (count <= 0) return;

  // Move cursor left
  std::cout << "\e[" << count << "D";

  // Clear characters
  for (int i = 0; i < count; i++) std::cout << ' ';

  // Move back again
  std::cout << "\e[" << count << "D";
  std::cout.flush();
}

void initCursor() { std::cout << "\x1b[2J\x1b[H" << std::flush; }

void UpFor(const int& num) {
  if (num > 0) {
    std::cout << "\e[" << num << "A" << std::flush;
  }
}

void downFor(const int& num) {
  if (num > 0) {
    std::cout << "\e[" << num << "B" << std::flush;
  }
}

void rFor(const int& num) {
  if (num > 0) {
    std::cout << "\e[" << num << "C" << std::flush;
  }
}

void lFor(const int& num) {
  if (num > 0) {
    std::cout << "\e[" << num << "D" << std::flush;
  }
}

void upForBeginOfLine(const int& num) {
  if (num > 0) {
    std::cout << "\e[" << num << "E" << std::flush;
  } else {
    std::cout << "\e[" << num << "F" << std::flush;
  }
}

void downForBeginOfLine(const int& num) {
  if (num > 0) {
    std::cout << "\e[" << num << "F" << std::flush;
  } else {
    std::cout << "\e[" << num << "E" << std::flush;
  }
}

void lTo(int num) {
  if (num >= 0) {
    std::cout << "\e[" << ++num << "G" << std::flush;
  }
}

void moveTo(int row, int col) {
  std::cout << "\e[" << (row + 1) << ";" << (col + 1) << "H" << std::flush;
}

int getTerminalColumns() {
  struct winsize w;
  return (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) != -1) ? w.ws_col : -1;
}

int getTerminalRows() {
  struct winsize w;
  return (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) != -1) ? w.ws_row : -1;
}

void getCursorPosition(int& row, int& col) {
  struct termios oldt, newt;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;

  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);

  std::cout << "\e[6n" << std::flush;

  char ch;
  if (std::cin.get(ch) && ch == '\e') {
    std::cin.get(ch);  // '['
    std::cin >> row;
    std::cin.get(ch);  // ';'
    std::cin >> col;
    std::cin.get(ch);  // 'R'
  }

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

void upScroll(const int& num) {
  if (num > 0) {
    std::cout << "\e[" << num << "S" << std::flush;
  } else {
    int new_n = num * -1;
    std::cout << "\e[" << num << "T" << std::flush;
  }
}

void downScroll(const int& num) {
  if (num > 0) {
    std::cout << "\e[" << num << "T" << std::flush;
  } else {
    int new_n = num * -1;
    std::cout << "\e[" << num << "S" << std::flush;
  }
}

void printBold(const char* str) {
  std::cout << "\e[1m" << str << "\e[0m" << std::flush;
}

void printThick(const char* str) {
  std::cout << "\e[2m" << str << "\e[0m" << std::flush;
}

void printItalic(const char* str) {
  std::cout << "\e[3m" << str << "\e[0m" << std::flush;
}

void printUnderline(const char* str) {
  std::cout << "\e[4m" << str << "\e[0m" << std::flush;
}

void printBlink(const char* str) {
  std::cout << "\e[5m" << str << "\e[0m" << std::flush;
}

void printFastBlink(const char* str) {
  std::cout << "\e[5m" << str << "\e[0m" << std::flush;
}

void printReverse(const char* str) {
  std::cout << "\e[7m" << str << "\e[0m" << std::flush;
}

void printHide(const char* str) {
  std::cout << "\e[8m" << str << "\e[0m" << std::flush;
}

void printCancel(const char* str) {
  std::cout << "\e[9m" << str << "\e[0m" << std::flush;
}
}  // namespace utils
}  // namespace terminal
