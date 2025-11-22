#include "obj.hpp"
#include "../base/base.hpp"

Object::Object(const std::string &text, int row, int col)
    : row(row), col(col), text(text), text_color(-1), fill_color(-1),
      show_flag(false) {}

Object::~Object() {
  if (show_flag)
    hide();
}

Object &Object::operator=(const std::string &new_text) {
  hide();
  text = new_text;
  show();
  return *this;
}

std::string &Object::operator()() { return text; }

void Object::show() {
  T_base::move(row, col);

  if (text_color >= 0)
    std::cout << "\033[" << text_color << "m";

  if (fill_color >= 0)
    std::cout << "\033[" << fill_color << "m";

  std::cout << text << "\033[0m" << std::flush;
  show_flag = true;
}

void Object::hide() {
  T_base::move(row, col);
  for (size_t i = 0; i < text.size(); ++i)
    std::cout << " ";
  std::cout << std::flush;
  show_flag = false;
};

void Object::move(int &new_row, int &new_col) {
  bool cf = show_flag;
  if (cf)
    hide();
  row = new_row;
  col = new_col;
  if (cf)
    show();
};

void Object::change_text_color(int color) {
  text_color = color;
  if (show_flag)
    show();
}

void Object::change_fill_color(int color) {
  fill_color = color;
  if (show_flag)
    show();
}

void Object::change_text_color(const std::string &color) {
  text_color = convert_color_name(color, true);
  if (show_flag)
    show();
}

void Object::change_fill_color(const std::string &color) {
  fill_color = convert_color_name(color, false);
  if (show_flag)
    show();
}

int Object::convert_color_name(const std::string &name, bool is_text) {
  if (is_text) {
    if (name == "red")
      return text_red;
    if (name == "green")
      return text_green;
    if (name == "yellow")
      return text_yellow;
    if (name == "blue")
      return text_blue;
    if (name == "magenta")
      return text_magenta;
    if (name == "cyan")
      return text_sian;
    if (name == "gray")
      return text_gray;
  } else {
    if (name == "red")
      return fill_red;
    if (name == "green")
      return fill_green;
    if (name == "yellow")
      return fill_yellow;
    if (name == "blue")
      return fill_blue;
    if (name == "magenta")
      return fill_magenta;
    if (name == "cyan")
      return fill_sian;
    if (name == "gray")
      return fill_gray;
  }
  return -1;
}

void Object::refresh() {
  if (show_flag)
    hide();
  show();
}

bool show_flag;
int row, col;
std::string text;
int text_color;
int fill_color;
int with;
int flags;
