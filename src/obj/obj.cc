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
  __terminal__::__manager__::ObjData data{};
  data.y = row;
  data.x = col;
  data.h = height;
  data.w = width;
  data.show = false;
  data.title = std::move(title);
  data.text = std::move(text);
  data.border = border;

  __terminal__::__manager__::register_object(self_id, data);
}

Object::~Object() {
  --cnt;
  if (__terminal__::__manager__::get_showing(self_id)) hide();
  __terminal__::__manager__::unregister_object(self_id);
}

Object& Object::operator=(const std::string& new_text) {
  bool was_show_flag = __terminal__::__manager__::get_showing(self_id);
  if (__terminal__::__manager__::get_showing(self_id)) hide();
  __terminal__::__manager__::set_text(self_id, new_text);
  if (was_show_flag) show();
  return *this;
}

Object& Object::operator+=(const std::string& append_text) {
  bool was_show_flag = __terminal__::__manager__::get_showing(self_id);
  if (__terminal__::__manager__::get_showing(self_id)) hide();
  std::string current_text = __terminal__::__manager__::get_text(self_id);
  current_text += append_text;
  __terminal__::__manager__::set_text(self_id, current_text);
  if (was_show_flag) show();
  return *this;
}

Object& Object::operator+=(const char append_char) {
  bool was_show_flag = __terminal__::__manager__::get_showing(self_id);
  if (__terminal__::__manager__::get_showing(self_id)) hide();
  std::string current_text = __terminal__::__manager__::get_text(self_id);
  current_text += append_char;
  __terminal__::__manager__::set_text(self_id, current_text);
  if (was_show_flag) show();
  return *this;
}

int Object::operator[](const int& num) {
  switch (num) {
    case 0:
      return __terminal__::__manager__::get_showing(self_id) ? 1 : 0;
    case 1:
      return __terminal__::__manager__::get_x(self_id);
    case 2:
      return __terminal__::__manager__::get_y(self_id);
    case 3:
      return __terminal__::__manager__::get_height(self_id);
    case 4:
      return __terminal__::__manager__::get_width(self_id);
    case 5:
      return __terminal__::__manager__::get_text_color(self_id);
    case 6:
      return __terminal__::__manager__::get_fill_color(self_id);
    case 7:
      return __terminal__::__manager__::get_border(self_id);
    default:
      throw std::out_of_range("Object::operator[] invalid index");
  }
}

std::string Object::operator()(const int& type) {
  if (type == 0)
    return __terminal__::__manager__::get_title(self_id);
  else if (type == 1)
    return __terminal__::__manager__::get_text(self_id);
  else
    throw std::out_of_range("Object::operator() invalid type");
}

Object& Object::clear() {
  __terminal__::__manager__::set_text(self_id, "");
  __terminal__::__manager__::set_title(self_id, "");
  __terminal__::__manager__::set_text_color(self_id, -1);
  __terminal__::__manager__::set_fill_color(self_id, -1);
  __terminal__::__manager__::set_flags(self_id, 0);
  return *this;
}

// =======================================================
// SHOW — now supports multi-line text
// =======================================================
Object& Object::show() {
  __terminal__::__manager__::set_show(self_id, true);
  return *this;
}

// =======================================================
// HIDE — correctly erases multi-line text
// =======================================================
Object& Object::hide() {
  __terminal__::__manager__::set_show(self_id, false);
  return *this;
}

// =======================================================

Object& Object::title(const std::string& new_title) {
  bool was_showing = __terminal__::__manager__::get_showing(self_id);
  if (was_showing) hide();
  __terminal__::__manager__::set_title(self_id, new_title);
  if (was_showing) show();
  return *this;
}

Object& Object::text(const std::string& new_text) {
  bool was_showing = __terminal__::__manager__::get_showing(self_id);
  if (was_showing) hide();
  __terminal__::__manager__::set_text(self_id, new_text);
  if (was_showing) show();
  return *this;
}

Object& Object::move(const int& new_row, const int& new_col) {
  bool was_showing = __terminal__::__manager__::get_showing(self_id);
  if (was_showing) hide();
  __terminal__::__manager__::set_x(self_id, new_row);
  __terminal__::__manager__::set_y(self_id, new_col);
  if (was_showing) show();
  return *this;
}

Object& Object::resize(const int& new_height, const int& new_width,
                       const int& border_type) {
  __terminal__::__manager__::set_width(self_id, new_width);
  __terminal__::__manager__::set_height(self_id, new_height);
  __terminal__::__manager__::set_border(self_id, border_type);
  return *this;
}

Object& Object::resize(const int& border_type) {
  __terminal__::__manager__::set_border(self_id, border_type);
  return *this;
}

Object& Object::changeTextColor(const int& color) {
  __terminal__::__manager__::set_text_color(self_id, color);
  return *this;
}

Object& Object::changeFillColor(const int& color) {
  __terminal__::__manager__::set_fill_color(self_id, color);
  return *this;
}

Object& Object::changeTextColor(const std::string& color) {
  int new_color = convert_color_name(color, true);
  __terminal__::__manager__::set_text_color(self_id, new_color);
  return *this;
}

Object& Object::changeFillColor(const std::string& color) {
  int new_color = convert_color_name(color, false);
  __terminal__::__manager__::set_fill_color(self_id, new_color);
  return *this;
}

int Object::convert_color_name(const std::string& name, const bool& is_text) {
  if (is_text) {
    if (name == "red") return terminal::utils::TextColor::text_red;
    if (name == "green") return terminal::utils::TextColor::text_green;
    if (name == "yellow") return terminal::utils::TextColor::text_yellow;
    if (name == "blue") return terminal::utils::TextColor::text_blue;
    if (name == "magenta") return terminal::utils::TextColor::text_magenta;
    if (name == "cyan") return terminal::utils::TextColor::text_cyan;
    if (name == "gray") return terminal::utils::TextColor::text_gray;
  } else {
    if (name == "red") return terminal::utils::FillColor::fill_red;
    if (name == "green") return terminal::utils::FillColor::fill_green;
    if (name == "yellow") return terminal::utils::FillColor::fill_yellow;
    if (name == "blue") return terminal::utils::FillColor::fill_blue;
    if (name == "magenta") return terminal::utils::FillColor::fill_magenta;
    if (name == "cyan") return terminal::utils::FillColor::fill_cyan;
    if (name == "gray") return terminal::utils::FillColor::fill_gray;
  }
  return -1;
}
}  // namespace terminal
