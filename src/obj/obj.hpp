#pragma once

#ifndef TERMINAL_LIBRARY_OBJECT_
#define TERMINAL_LIBRARY_OBJECT_

#include <string>

namespace terminal {

class Object {
public:
  Object(const std::string &text, const int &row, const int &col,
         const int &width, const int &hight, int &border);
  ~Object();

  Object operator=(const std::string &new_text);

  // 0-show,1-row,2-col,3-width,4-hight,5-text_width,6-text_hight,7-text_color,8-fill_color,9-board,flags...
  int operator[](int num);
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
  void show_border();

  bool show_flag = false;
  int row = 0, col = 0;
  int width = 0, hight = 0;
  int border_flag = false;
  std::string text;
  int text_color = -1;
  int fill_color = -1;
  int text_hight = 1;
  int text_width = 0;
  // 0-italic 1-under 2-text_width
  int flags = 0;
};

} // namespace terminal

#endif
