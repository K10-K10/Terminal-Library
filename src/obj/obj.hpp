#ifndef __terminal_object
#define __terminal_object
#include "../base/base.hpp"
#include "../color/color.hpp"
#include <string>

class Object {
public:
  Object(const std::string &text, int row, int col);
  ~Object();

  Object &operator=(const std::string &new_text);
  std::string &operator()();
  void init();
  void show();
  void hide();
  void move(int &new_row, int &new_col);

  void change_text_color(int color);

  void change_fill_color(int color);
  void change_text_color(const std::string &color);
  void change_fill_color(const std::string &color);

private:
  int convert_color_name(const std::string &name, bool is_text);
  void refresh();
  bool show_flag;
  int row, col;
  std::string text;
  int text_color;
  int fill_color;
  int with;
  int flags;
};

#endif
