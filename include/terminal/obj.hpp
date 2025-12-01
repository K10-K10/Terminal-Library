#pragma once

#ifndef TERMINAL_LIBRARY_OBJECT_
#define TERMINAL_LIBRARY_OBJECT_

#include <string>

namespace terminal {

class Object {
public:
  Object(const std::string &text, const int &row, const int &col);
  ~Object();

  Object &operator=(const std::string &new_text);

  // 0-row,1-col,2-high,3-width,4-text_color,5-fill_color
  int &operator[](int num);
  std::string &operator()();

  void clear();

  void show();
  void hide();

  void move(int new_row, int new_col);

  void change_text_color(const int &color);
  void change_fill_color(const int &color);
  void change_text_color(const std::string &color);
  void change_fill_color(const std::string &color);

private:
  int convert_color_name(const std::string &name, const bool &is_text);
  void refresh();
  void text_size();

  bool show_flag = false;
  int row = 0, col = 0;
  std::string text;
  int text_color = -1;
  int fill_color = -1;
  int high = 1;
  int width = 0;
  // 0-italic 1-under 2-width
  int flags = 0;
};

} // namespace terminal

#endif
