#include "utils/color.h"

#include <iostream>

namespace terminal {
int print_color(const int& txt_color, const char* str) {
  if (37 >= txt_color && txt_color >= 30) {
    std::cout << "\e[" << txt_color << "m" << str << "\e[0m " << std::flush;
    return 0;
  } else {
    return -1;
  }
}

int print_color(const int& txt_color, const int& fill_color, const char* str) {
  if (37 >= txt_color && txt_color >= 30 && 47 >= fill_color &&
      fill_color >= 40) {
    std::cout << "\e[" << txt_color << "m" << "\e[" << txt_color << "m" << str
              << "\e[0m " << std::flush;
    return 0;
  } else {
    return -1;
  }
}

}  // namespace terminal
