#ifndef __terminal_object
#define __terminal_object
#include "../base/base.hpp"
#include "../color/color.hpp"
#include <string>

class Object {
public:
  Object(const std::string &text, const int &row, const int &col);
  ~Object();

  Object &operator=(const std::string &new_text);
  // 0-row,1-col,2,high,3-width,4-text_color,5-fill_color
  int &operator[](int num);
  std::string &operator()();

  void clear();

  void show();
  void hide();

  // Move the object to (new_row,new_col)
  void move(int &new_row, int &new_col);

  void change_text_color(const int &color);
  void change_fill_color(const int &color);
  void change_text_color(const std::string &color);
  void change_fill_color(const std::string &color);

private:
  int convert_color_name(const std::string &name, const bool &is_text);
  void refresh();
  void text_size();
  bool show_flag;
  int row, col;
  std::string text;
  int text_color;
  int fill_color;
  int high;
  int width;
  int flags;
};

#endif
