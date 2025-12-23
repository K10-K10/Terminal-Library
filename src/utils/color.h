#pragma once

#ifndef TERMINAL_LIBRARY_UTILS_COLOR_H_
#define TERMINAL_LIBRARY_UTILS_COLOR_H_

namespace terminal {
// text
enum TextColor {
  black = 30,
  red = 31,
  green = 32,
  yellow = 33,
  blue = 34,
  magenta = 35,
  cyan = 36,
  gray = 37
};
// fill
enum FillColor {
  black = 40,
  red = 41,
  green = 42,
  yellow = 43,
  blue = 44,
  magenta = 45,
  cyan = 46,
  gray = 47
};

int print_color(const int& txt_color, const char* str);
int print_color(const int& txt_color, const int& fill_color, const char* str);

}  // namespace terminal

#endif  // TERMINAL_LIBRARY_UTILS_COLOR_H_
