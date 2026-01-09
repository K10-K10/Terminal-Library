#include "obj/obj.h"

#include <algorithm>
#include <iostream>
#include <string>

#include "obj/manager.h"
#include "utils/base.h"
#include "utils/color.h"

namespace terminal {
Object::getect(std::string title, std::string text, int row, int col,
               int height, int width, int border) {
  static std::atomic<int> cnt{0};
  self_id = ++cnt;

  terminal_manager::getData data{};
  data.y = row;
  data.x = col;
  data.h = height;
  data.w = width;
  data.show = false;
  data.title = std::move(title);
  data.text = std::move(text);
  data.border = border;

  terminal_manager::register_object(self_id, data);
}

Object::~Object() {
  --cnt;
  if (terminal_manager::get_showing(self_id)) hide();
  terminal_manager::unregister_object(self_id);
}

Object& Object::operator=(const std::string& new_text) {
  bool was_show_flag = terminal_manager::get_showing(self_id);
  if (terminal_manager::get_showing(self_id)) hide();
  self_data.text = new_text;
  if (was_show_flag) show();
  terminal_manager::update(self_id, self_data);
  return *this;
}

int Object::operator[](const int& num) {
  switch (num) {
    case 0:
      return terminal_manager::get_showing(self_id) ? 1 : 0;
    case 1:
      return terminal_manager::get_x(self_id);
    case 2:
      return terminal_manager::get_y(self_id);
    case 3:
      return terminal_manager::get_height(self_id);
    case 4:
      return terminal_manager::get_width(self_id);
    case 5:
      return terminal_manager::get_text_color(self_id);
    case 6:
      return terminal_manager::get_fill_color(self_id);
    case 7:
      return terminal_manager::get_border(self_id);
    default:
      throw std::out_of_range("Object::operator[] invalid index");
  }
}

std::string Object::operator()(const int& type) {
  if (type == 0)
    return terminal_manager::get_title(self_id);
  else if (type == 1)
    return terminal_manager::get_text(self_id);
  else
    throw std::out_of_range("Object::operator() invalid type");
}

Object& Object::clear() {
  self_data.text = "";
  self_data.text_color = -1;
  self_data.fill_color = -1;
  self_data.flags = 0;
  terminal_manager::update(self_id, self_data);
  return *this;
}

// =======================================================
// SHOW — now supports multi-line text
// =======================================================
Object& Object::show() {
  self_data.show = true;
  terminal_manager::update(self_id, self_data);
  return *this;
}

// =======================================================
// HIDE — correctly erases multi-line text
// =======================================================
Object& Object::hide() {
  if (!terminal_manager::get_showing(self_id)) return *this;
  self_data.show = false;
  terminal_manager::update(self_id, self_data);
  return *this;
}

// =======================================================

Object& Object::move(const int& new_row, const int& new_col) {
  bool was_showing = terminal_manager::get_showing(self_id);
  if (was_showing) hide();
  self_data.x = new_row;
  self_data.y = new_col;
  if (was_showing) show();
  terminal_manager::update(self_id, self_data);
  return *this;
}

Object& Object::resize(const int& new_height, const int& new_width,
                       const int& border_type) {
  hide();
  self_data.w = new_width;
  self_data.h = new_height;
  self_data.border = border_type;
  terminal_manager::update(self_id, self_data);
  return *this;
}

Object& Object::resize(const int& border_type) {
  self_data.border = border_type;
  terminal_manager::update(self_id, self_data);
  return *this;
}

Object& Object::change_text_color(const int& color) {
  self_data.text_color = color;
  terminal_manager::update(self_id, self_data);
  return *this;
}

Object& Object::change_fill_color(const int& color) {
  self_data.fill_color = color;
  terminal_manager::update(self_id, self_data);
  return *this;
}

Object& Object::change_text_color(const std::string& color) {
  self_data.text_color = convert_color_name(color, true);
  terminal_manager::update(self_id, self_data);
  return *this;
}

Object& Object::change_fill_color(const std::string& color) {
  self_data.fill_color = convert_color_name(color, false);
  terminal_manager::update(self_id, self_data);
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
