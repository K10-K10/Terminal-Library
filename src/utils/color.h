#pragma once

#ifndef TERMINAL_LIBRARY_UTILS_COLOR_H_
#define TERMINAL_LIBRARY_UTILS_COLOR_H_

namespace terminal {
// text
enum TextColor {
  text_black = 30,
  text_red = 31,
  text_green = 32,
  text_yellow = 33,
  text_blue = 34,
  text_magenta = 35,
  text_cyan = 36,
  text_gray = 37
};
// fill
enum FillColor {
  fill_black = 40,
  fill_red = 41,
  fill_green = 42,
  fill_yellow = 43,
  fill_blue = 44,
  fill_magenta = 45,
  fill_cyan = 46,
  fill_gray = 47
};

int print_color(const int& txt_color, const char* str);
int print_color(const int& txt_color, const int& fill_color, const char* str);

}  // namespace terminal

#endif  // TERMINAL_LIBRARY_UTILS_COLOR_H_
