#include "obj/obj.h"

#include <algorithm>
#include <iostream>
#include <string>

#include "obj/manager.h"
#include "utils/base.h"
#include "utils/color.h"

namespace terminal {
Object::Object(const std::string& title, const std::string& text, const int row,
               const int col, const int height, const int width,
               const int border) {
  static std::atomic<int> cnt{0};
  self_id = ++cnt;
  _terminal_manager::ObjData data{};
  data.y = row;
  data.x = col;
  data.h = height;
  data.w = width;
  data.show = false;
  data.title = std::move(title);
  data.text = std::move(text);
  data.border = border;

  _terminal_manager::register_object(self_id, data);
}

Object::~Object() {
  --cnt;
  if (_terminal_manager::get_showing(self_id)) hide();
  _terminal_manager::unregister_object(self_id);
}

Object& Object::operator=(const std::string& new_text) {
  bool was_show_flag = _terminal_manager::get_showing(self_id);
  if (_terminal_manager::get_showing(self_id)) hide();
  _terminal_manager::set_text(self_id, new_text);
  if (was_show_flag) show();
  return *this;
}

Object& Object::operator+=(const std::string& append_text) {
  bool was_show_flag = _terminal_manager::get_showing(self_id);
  if (_terminal_manager::get_showing(self_id)) hide();
  std::string current_text = _terminal_manager::get_text(self_id);
  current_text += append_text;
  _terminal_manager::set_text(self_id, current_text);
  if (was_show_flag) show();
  return *this;
}

int Object::operator[](const int& num) {
  switch (num) {
    case 0:
      return _terminal_manager::get_showing(self_id) ? 1 : 0;
    case 1:
      return _terminal_manager::get_x(self_id);
    case 2:
      return _terminal_manager::get_y(self_id);
    case 3:
      return _terminal_manager::get_height(self_id);
    case 4:
      return _terminal_manager::get_width(self_id);
    case 5:
      return _terminal_manager::get_text_color(self_id);
    case 6:
      return _terminal_manager::get_fill_color(self_id);
    case 7:
      return _terminal_manager::get_border(self_id);
    default:
      throw std::out_of_range("Object::operator[] invalid index");
  }
}

std::string Object::operator()(const int& type) {
  if (type == 0)
    return _terminal_manager::get_title(self_id);
  else if (type == 1)
    return _terminal_manager::get_text(self_id);
  else
    throw std::out_of_range("Object::operator() invalid type");
}

Object& Object::clear() {
  _terminal_manager::set_text(self_id, "");
  _terminal_manager::set_title(self_id, "");
  _terminal_manager::set_text_color(self_id, -1);
  _terminal_manager::set_fill_color(self_id, -1);
  _terminal_manager::set_flags(self_id, 0);
  return *this;
}

// =======================================================
// SHOW — now supports multi-line text
// =======================================================
Object& Object::show() {
  _terminal_manager::set_show(self_id, true);
  return *this;
}

// =======================================================
// HIDE — correctly erases multi-line text
// =======================================================
Object& Object::hide() {
  _terminal_manager::set_show(self_id, false);
  return *this;
}

// =======================================================

Object& Object::move(const int& new_row, const int& new_col) {
  bool was_showing = _terminal_manager::get_showing(self_id);
  if (was_showing) hide();
  _terminal_manager::set_x(self_id, new_row);
  _terminal_manager::set_y(self_id, new_col);
  if (was_showing) show();
  return *this;
}

Object& Object::resize(const int& new_height, const int& new_width,
                       const int& border_type) {
  _terminal_manager::set_width(self_id, new_width);
  _terminal_manager::set_height(self_id, new_height);
  _terminal_manager::set_border(self_id, border_type);
  return *this;
}

Object& Object::resize(const int& border_type) {
  _terminal_manager::set_border(self_id, border_type);
  return *this;
}

Object& Object::changeTextColor(const int& color) {
  _terminal_manager::set_text_color(self_id, color);
  return *this;
}

Object& Object::changeFillColor(const int& color) {
  _terminal_manager::set_fill_color(self_id, color);
  return *this;
}

Object& Object::changeTextColor(const std::string& color) {
  int new_color = convert_color_name(color, true);
  _terminal_manager::set_text_color(self_id, new_color);
  return *this;
}

Object& Object::changeFillColor(const std::string& color) {
  int new_color = convert_color_name(color, false);
  _terminal_manager::set_fill_color(self_id, new_color);
  return *this;
}

int Object::convert_color_name(const std::string& name, const bool& is_text) {
  if (is_text) {
    if (name == "red") return terminal::TextColor::text_red;
    if (name == "green") return terminal::TextColor::text_green;
    if (name == "yellow") return terminal::TextColor::text_yellow;
    if (name == "blue") return terminal::TextColor::text_blue;
    if (name == "magenta") return terminal::TextColor::text_magenta;
    if (name == "cyan") return terminal::TextColor::text_cyan;
    if (name == "gray") return terminal::TextColor::text_gray;
  } else {
    if (name == "red") return terminal::FillColor::fill_red;
    if (name == "green") return terminal::FillColor::fill_green;
    if (name == "yellow") return terminal::FillColor::fill_yellow;
    if (name == "blue") return terminal::FillColor::fill_blue;
    if (name == "magenta") return terminal::FillColor::fill_magenta;
    if (name == "cyan") return terminal::FillColor::fill_cyan;
    if (name == "gray") return terminal::FillColor::fill_gray;
  }
  return -1;
}
}  // namespace terminal
