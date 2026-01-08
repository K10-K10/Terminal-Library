#include "obj/obj.h"

#include <algorithm>
#include <iostream>
#include <string>

#include "obj/manager.h"
#include "utils/base.h"
#include "utils/color.h"

namespace terminal {
Object::Object(const std::string& title, const std::string& text,
               const int& row, const int& col, const int& height,
               const int& width, const int& border) {
  ++cnt;
  self_id = cnt;
  self_data.gen = 0;  // TODO(K10-K10): add gen
  self_data.x = row;
  self_data.y = col;
  self_data.w = width;
  self_data.h = height;
  self_data.show = false;
  if (terminal_manager::selected_obj_id == -1)
    terminal_manager::selected_obj_id = self_id;
  terminal_manager::register_object(this, self_data);
  text_size();
}

Object::~Object() {
  --cnt;
  if (terminal_manager::is_showing(this)) hide();
  terminal_manager::unregister_object(this);
}

Object& Object::operator=(const std::string& new_text) {
  bool was_show_flag = terminal_manager::is_showing(this);
  if (terminal_manager::is_showing(this)) hide();
  self_data.text = new_text;
  text_size();
  if (was_show_flag) show();
  terminal_manager::update(this, self_data);
  return *this;
}

int Object::operator[](const int& num) {
  switch (num) {
    case 0:
      return terminal_manager::is_showing(this) ? 1 : 0;
    case 1:
      return terminal_manager::obj_x(this);
    case 2:
      return terminal_manager::obj_y(this);
    case 3:
      return terminal_manager::obj_height(this);
    case 4:
      return terminal_manager::obj_width(this);
    case 5:
      return self_data.text_color;
    case 6:
      return self_data.fill_color;
    case 7:
      return self_data.border;
    default:
      throw std::out_of_range("Object::operator[] invalid index");
  }
}

std::string& Object::operator()(const int& type) {
  if (type == 0)
    return title;
  else if (type == 1)
    return text;
  else
    throw std::out_of_range("Object::operator() invalid type");
}

Object& Object::clear() {
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
Object& Object::show() {
  int col = self_data.y;
  if (flags & (1 << 0))  // Italic
    std::cout << "\e[3m";
  if (flags & (1 << 1))  // under_bar
    std::cout << "\e[4m";
  if (flags & (1 << 2)) std::cout << "\e[1m";  // bold
  text_size();
  self_data.show = true;
  terminal_manager::update(this, self_data);
  show_border();
  int text_start_col = col + 2;
  terminal::utils::MoveTo(terminal_manager::obj_x(this), text_start_col);
  for (size_t i = 0;
       i < std::min(title.size(),
                    static_cast<size_t>(terminal_manager::obj_width(this) - 1));
       ++i) {
    std::cout << title[i];
  }

  int text_start_row = terminal_manager::obj_x(this) + 2;
  terminal::utils::MoveTo(text_start_row, text_start_col);
  int current_row = text_start_row;
  int current_col = text_start_col;
  size_t start = 0;
  while (true) {
    if (current_row >=
        terminal_manager::obj_x(this) + terminal_manager::obj_height(this) - 1)
      break;
    size_t end = text.find('\n', start);
    std::string line = (end == std::string::npos)
                           ? text.substr(start)
                           : text.substr(start, end - start);
    std::cout << "\e[" << current_row << ";" << text_start_col << "H";
    if (text_color >= 0) std::cout << "\e[" << text_color << "m";
    if (fill_color >= 0) std::cout << "\e[" << fill_color << "m";
    std::cout << line.substr(0, terminal_manager::obj_width(this) - 2);
    if (end == std::string::npos) break;
    start = end + 1;
    current_row++;
  }
  std::cout << "\e[0m" << std::flush;
  self_data.show = true;
  terminal_manager::update(this,
                           self_data);  // TODO(K10-K10): update in field class?
  return *this;
}

// =======================================================
// HIDE — correctly erases multi-line text
// =======================================================
Object& Object::hide() {
  if (!terminal_manager::is_showing(this)) return *this;
  text_size();
  int r = terminal_manager::obj_x(this);
  int c = terminal_manager::obj_y(this);
  for (int j = 0; j < terminal_manager::obj_height(this); ++j) {
    terminal::utils::MoveTo(terminal_manager::obj_x(this) + j,
                            terminal_manager::obj_y(this));
    for (int i = 0; i < terminal_manager::obj_width(this); ++i) {
      std::cout << ' ';
    }
  }

  std::cout << std::flush;
  self_data.show = false;
  terminal_manager::update(this, self_data);

  return *this;
}

// =======================================================

Object& Object::move(const int& new_row, const int& new_col) {
  bool was_showing = terminal_manager::is_showing(this);
  if (was_showing) hide();
  self_data.x = new_row;
  self_data.y = new_col;
  if (was_showing) show();
  terminal_manager::update(this, self_data);
  return *this;
}

Object& Object::resize(const int& new_height, const int& new_width,
                       const int& border_type) {
  hide();
  self_data.w = new_width;
  self_data.h = new_height;
  border_flag = border_type;
  refresh();
  terminal_manager::update(this, self_data);
  return *this;
}

Object& Object::resize(const int& border_type) {
  border_flag = border_type;
  refresh();
  return *this;
}

Object& Object::change_text_color(const int& color) {
  text_color = color;
  refresh();
  return *this;
}

Object& Object::change_fill_color(const int& color) {
  fill_color = color;
  refresh();
  return *this;
}

Object& Object::change_text_color(const std::string& color) {
  text_color = convert_color_name(color, true);
  refresh();
  return *this;
}

Object& Object::change_fill_color(const std::string& color) {
  fill_color = convert_color_name(color, false);
  refresh();
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

void Object::refresh() {
  text_size();
  if (terminal_manager::is_showing(this)) hide();
  show();
}

int Object::show_border() {
  if (border_flag == 0) return 0;

  if (border_flag != 1) return -1;

  int top = terminal_manager::obj_x(this);
  int left = terminal_manager::obj_y(this);
  int bottom = top + terminal_manager::obj_height(this);
  int right = left + terminal_manager::obj_width(this);

  // ┌───┐
  terminal::utils::MoveTo(top, left);
  std::cout << "┌";
  for (int c = left + 1; c < right - 1; ++c) std::cout << "─";
  std::cout << "┐";

  // │   │
  for (int r = top + 1; r < bottom - 1; ++r) {
    terminal::utils::MoveTo(r, left);
    std::cout << "│";
    terminal::utils::MoveTo(r, right - 1);
    std::cout << "│";
  }

  // └───┘
  terminal::utils::MoveTo(bottom - 1, left);
  std::cout << "└";
  for (int c = left + 1; c < right - 1; ++c) std::cout << "─";
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
