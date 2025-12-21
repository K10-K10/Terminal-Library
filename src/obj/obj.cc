#include "obj/obj.h"

#include <algorithm>
#include <iostream>
#include <string>

#include "utils/base.h"
#include "utils/color.h"

namespace terminal {
int Object::cnt = 0;

Object::Object(const std::string& title, const std::string& text,
               const int& row, const int& col, const int& width,
               const int& height, const int& border)
    : title(title),
      row(row),
      col(col),
      width(width),
      height(height),
      text(text),
      text_color(-1),
      fill_color(-1),
      show_flag(false),
      border_flag(border) {
  ++cnt;
  self_id = cnt;
  self_data.gen = 0;  // TODO: add gen
  self_data.x = row;
  self_data.y = col;
  self_data.w = width;
  self_data.h = height;
  self_data.show = false;
  terminal_manager::obj_map[self_id] = self_data;
  text_size();
}

Object::~Object() {
  --cnt;
  terminal_manager::obj_map.erase(self_id);
  if (show_flag) hide();
}

Object Object::operator=(const std::string& new_text) {
  bool was_show_flag = show_flag;
  if (show_flag) hide();
  text = new_text;
  text_size();
  if (was_show_flag) show();
  return *this;
}

int Object::operator[](const int& num) {
  switch (num) {
    case 0:
      return show_flag ? 1 : 0;
    case 1:
      return row;
    case 2:
      return col;
    case 3:
      return width;
    case 4:
      return height;
    case 5:
      return text_width;
    case 6:
      return text_height;
    case 7:
      return text_color;
    case 8:
      return fill_color;
    case 9:
      return border_flag ? 1 : 0;
    default:
      throw std::out_of_range("Object::operator[] invalid index");
  }
}

std::string& Object::operator()() { return text; }

Object Object::clear() {
  text = "";
  text_color = -1;
  fill_color = -1;
  flags = 0;
  refresh();
  return *this;
}

// =======================================================
// SHOW — now supports multi-line text
// =======================================================
Object Object::show() {
  text_size();
  show_flag = true;
  show_border();
  terminal::MoveTo(row, col);
  int current_row = row;
  size_t start = 0;

  if (flags & (1 << 0))  // Italic
    std::cout << "\e[3m" << std::flush;
  if (flags & (1 << 1))  // under_bar
    std::cout << "\e[4m" << std::flush;
  if (flags & (2 << 1)) std::cout << "\e[1m" << std::flush;
  while (true) {
    size_t end = text.find('\n', start);
    std::string line = (end == std::string::npos)
                           ? text.substr(start)
                           : text.substr(start, end - start);

    std::cout << "\e[" << current_row << ";" << col << "H";

    // colors
    if (text_color >= 0) std::cout << "\e[" << text_color << "m";
    if (fill_color >= 0) std::cout << "\e[" << fill_color << "m";

    std::cout << line << std::flush;

    if (end == std::string::npos) break;

    start = end + 1;
    current_row++;
  }
  if (flags & (1 << 0)) std::cout << "\e[23m" << std::flush;
  std::cout << "\e[0m" << std::flush;
  self_data.show = true;
  terminal_manager::obj_map[self_id] = self_data;
  return *this;
}

// =======================================================
// HIDE — correctly erases multi-line text
// =======================================================
Object Object::hide() {
  if (!show_flag) return *this;

  text_size();

  int current_row = row;

  for (int i = 0; i < text_height; ++i) {
    terminal::MoveTo(current_row, col);

    for (int j = 0; j < text_width; ++j) std::cout << ' ';

    current_row++;
  }

  std::cout << std::flush;
  show_flag = false;
  self_data.show = false;
  terminal_manager::obj_map[self_id] = self_data;
}

// =======================================================

Object Object::move(const int& new_row, const int& new_col) {
  bool was_showing = show_flag;
  if (was_showing) hide();
  row = new_row;
  col = new_col;
  if (was_showing) show();
  self_data.x = row;
  self_data.y = col;
  terminal_manager::obj_map[self_id] = self_data;
  return *this;
}

Object Object::resize(const int& new_width, const int& new_height,
                      const int& border_type) {
  width = new_width;
  height = new_height;
  border_flag = border_type;
  refresh();
  self_data.w = width;
  self_data.h = height;
  terminal_manager::obj_map[self_id] = self_data;
  return *this;
}

Object Object::resize(const int& border_type) {
  border_flag = border_type;
  refresh();
  return *this;
}

Object Object::change_text_color(const int& color) {
  text_color = color;
  refresh();
  return *this;
}

Object Object::change_fill_color(const int& color) {
  fill_color = color;
  refresh();
  return *this;
}

Object Object::change_text_color(const std::string& color) {
  text_color = convert_color_name(color, true);
  refresh();
  return *this;
}

Object Object::change_fill_color(const std::string& color) {
  fill_color = convert_color_name(color, false);
  refresh();
  return *this;
}

int Object::convert_color_name(const std::string& name, const bool& is_text) {
  if (is_text) {
    if (name == "red") return text_red;
    if (name == "green") return text_green;
    if (name == "yellow") return text_yellow;
    if (name == "blue") return text_blue;
    if (name == "magenta") return text_magenta;
    if (name == "cyan") return text_sian;
    if (name == "gray") return text_gray;
  } else {
    if (name == "red") return fill_red;
    if (name == "green") return fill_green;
    if (name == "yellow") return fill_yellow;
    if (name == "blue") return fill_blue;
    if (name == "magenta") return fill_magenta;
    if (name == "cyan") return fill_sian;
    if (name == "gray") return fill_gray;
  }
  return -1;
}

void Object::refresh() {
  text_size();
  if (show_flag) hide();
  show();
}

int Object::show_border() {
  if (border_flag == 0) return 0;

  if (border_flag != 1) return -1;

  int top = row;
  int left = col;
  int bottom = row + height - 1;
  int right = col + width - 1;

  // ┌───┐
  terminal::MoveTo(top, left);
  std::cout << "┌";
  for (int c = left + 1; c < right; ++c) std::cout << "─";
  std::cout << "┐";

  // │   │
  for (int r = top + 1; r < bottom; ++r) {
    terminal::MoveTo(r, left);
    std::cout << "│";
    terminal::MoveTo(r, right);
    std::cout << "│";
  }

  // └───┘
  terminal::MoveTo(bottom, left);
  std::cout << "└";
  for (int c = left + 1; c < right; ++c) std::cout << "─";
  std::cout << "┘";

  std::cout << std::flush;
  return 0;
}

// =======================================================
// text_size — better multi-line support
// =======================================================
void Object::text_size() {
  text_height = 1;
  text_width = 0;

  int current_text_width = 0;

  for (char c : text) {
    if (c == '\n') {
      text_width = std::max(text_width, current_text_width);
      text_height++;
      current_text_width = 0;
    } else {
      current_text_width++;
    }
  }
  text_width = std::max(text_width, current_text_width);
}
}  // namespace terminal
