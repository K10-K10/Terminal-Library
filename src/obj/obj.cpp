#include "obj.hpp"
#include "../base/base.hpp"
#include <stdexcept>

Object::Object(const std::string &text, const int &row, const int &col)
    : row(row), col(col), text(text), text_color(-1), fill_color(-1),
      show_flag(false) {
  text_size();
}

Object::~Object() {
  if (show_flag)
    hide();
}

Object &Object::operator=(const std::string &new_text) {
  if (show_flag)
    hide();
  text = new_text;
  text_size();
  show();
  return *this;
}

int &Object::operator[](int num) {
  switch (num) {
  case 0:
    return row;
  case 1:
    return col;
  case 2:
    return high;
  case 3:
    return width;
  default:
    throw std::out_of_range("Object::operator[] invalid index");
  }
}

std::string &Object::operator()() { return text; }

// =======================================================
// SHOW — now supports multi-line text
// =======================================================
void Object::show() {
  text_size();
  T_base::move(row, col);

  // color settings
  if (text_color >= 0)
    std::cout << "\033[" << text_color << "m";
  if (fill_color >= 0)
    std::cout << "\033[" << fill_color << "m";

  // draw line-by-line
  int current_row = row;
  size_t start = 0;

  while (true) {
    size_t end = text.find('\n', start);
    std::string line = (end == std::string::npos)
                           ? text.substr(start)
                           : text.substr(start, end - start);

    T_base::move(current_row, col);
    std::cout << line << "\033[0m" << std::flush;

    if (end == std::string::npos)
      break;

    start = end + 1;
    current_row++;
  }

  show_flag = true;
}

// =======================================================
// HIDE — correctly erases multi-line text
// =======================================================
void Object::hide() {
  text_size();
  int current_row = row;

  for (int i = 0; i < high; i++) {
    T_base::move(current_row, col);
    for (int j = 0; j < width; j++)
      std::cout << " ";
    current_row++;
  }

  std::cout << std::flush;
  show_flag = false;
}

// =======================================================

void Object::move(int &new_row, int &new_col) {
  bool was_showing = show_flag;
  if (was_showing)
    hide();
  row = new_row;
  col = new_col;
  if (was_showing)
    show();
}

void Object::change_text_color(const int &color) {
  text_color = color;
  refresh();
}

void Object::change_fill_color(const int &color) {
  fill_color = color;
  refresh();
}

void Object::change_text_color(const std::string &color) {
  text_color = convert_color_name(color, true);
  refresh();
}

void Object::change_fill_color(const std::string &color) {
  fill_color = convert_color_name(color, false);
  refresh();
}

int Object::convert_color_name(const std::string &name, const bool &is_text) {
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
  if (show_flag) {
    hide();
    show();
  }
}

// =======================================================
// text_size — better multi-line support
// =======================================================
void Object::text_size() {
  high = 1;
  width = 0;

  int current_width = 0;

  for (char c : text) {
    if (c == '\n') {
      width = std::max(width, current_width);
      high++;
      current_width = 0;
    } else {
      current_width++;
    }
  }
  width = std::max(width, current_width);
}
