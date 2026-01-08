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
  terminal_manager::register_object(self_id, self_data);
  text_size();
}

Object::~Object() {
  --cnt;
  if (terminal_manager::is_showing(self_id)) hide();
  terminal_manager::unregister_object(self_id);
}

Object& Object::operator=(const std::string& new_text) {
  bool was_show_flag = terminal_manager::is_showing(self_id);
  if (terminal_manager::is_showing(self_id)) hide();
  self_data.text = new_text;
  text_size();
  if (was_show_flag) show();
  terminal_manager::update(self_id, self_data);
  return *this;
}

int Object::operator[](const int& num) {
  switch (num) {
    case 0:
      return terminal_manager::is_showing(self_id) ? 1 : 0;
    case 1:
      return terminal_manager::obj_x(self_id);
    case 2:
      return terminal_manager::obj_y(self_id);
    case 3:
      return terminal_manager::obj_height(self_id);
    case 4:
      return terminal_manager::obj_width(self_id);
    case 5:
      return terminal_manager::obj_text_color(self_id);
    case 6:
      return terminal_manager::obj_fill_color(self_id);
    case 7:
      return terminal_manager::obj_border(self_id);
    default:
      throw std::out_of_range("Object::operator[] invalid index");
  }
}

std::string Object::operator()(const int& type) {
  if (type == 0)
    return terminal_manager::obj_title(self_id);
  else if (type == 1)
    return terminal_manager::obj_text(self_id);
  else
    throw std::out_of_range("Object::operator() invalid type");
}

Object& Object::clear() {
  self_data.text = "";
  self_data.text_color = -1;
  self_data.fill_color = -1;
  self_data.flags = 0;
  refresh();
  terminal_manager::update(self_id, self_data);
  return *this;
}

// =======================================================
// SHOW — now supports multi-line text
// =======================================================
Object& Object::show() {
  int col = self_data.y;
  if (terminal_manager::obj_flags(self_id) & (1 << 0))  // Italic
    std::cout << "\e[3m";
  if (terminal_manager::obj_flags(self_id) & (1 << 1))  // under_bar
    std::cout << "\e[4m";
  if (terminal_manager::obj_flags(self_id) & (1 << 2))
    std::cout << "\e[1m";  // bold
  text_size();
  self_data.show = true;
  terminal_manager::update(self_id, self_data);
  show_border();
  int text_start_col = col + 2;
  terminal::utils::MoveTo(terminal_manager::obj_x(self_id), text_start_col);
  for (size_t i = 0;
       i <
       std::min(terminal_manager::obj_title(self_id).size(),
                static_cast<size_t>(terminal_manager::obj_width(self_id) - 1));
       ++i) {
    std::cout << terminal_manager::obj_title(self_id)[i];
  }

  int text_start_row = terminal_manager::obj_x(self_id) + 2;
  terminal::utils::MoveTo(text_start_row, text_start_col);
  int current_row = text_start_row;
  int current_col = text_start_col;
  size_t start = 0;
  while (true) {
    if (current_row >= terminal_manager::obj_x(self_id) +
                           terminal_manager::obj_height(self_id) - 1)
      break;
    size_t end = terminal_manager::obj_text(self_id).find('\n', start);
    std::string line =
        (end == std::string::npos)
            ? terminal_manager::obj_text(self_id).substr(start)
            : terminal_manager::obj_text(self_id).substr(start, end - start);
    std::cout << "\e[" << current_row << ";" << text_start_col << "H";
    if (terminal_manager::obj_text_color(self_id) >= 0)
      std::cout << "\e[" << terminal_manager::obj_text_color(self_id) << "m";
    if (terminal_manager::obj_fill_color(self_id) >= 0)
      std::cout << "\e[" << terminal_manager::obj_fill_color(self_id) << "m";
    std::cout << line.substr(0, terminal_manager::obj_width(self_id) - 2);
    if (end == std::string::npos) break;
    start = end + 1;
    current_row++;
  }
  std::cout << "\e[0m" << std::flush;
  self_data.show = true;
  terminal_manager::update(self_id,
                           self_data);  // TODO(K10-K10): update in field class?
  return *this;
}

// =======================================================
// HIDE — correctly erases multi-line text
// =======================================================
Object& Object::hide() {
  if (!terminal_manager::is_showing(self_id)) return *this;
  text_size();
  int r = terminal_manager::obj_x(self_id);
  int c = terminal_manager::obj_y(self_id);
  for (int j = 0; j < terminal_manager::obj_height(self_id); ++j) {
    terminal::utils::MoveTo(terminal_manager::obj_x(self_id) + j,
                            terminal_manager::obj_y(self_id));
    for (int i = 0; i < terminal_manager::obj_width(self_id); ++i) {
      std::cout << ' ';
    }
  }

  std::cout << std::flush;
  self_data.show = false;
  terminal_manager::update(self_id, self_data);

  return *this;
}

// =======================================================

Object& Object::move(const int& new_row, const int& new_col) {
  bool was_showing = terminal_manager::is_showing(self_id);
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
  refresh();
  terminal_manager::update(self_id, self_data);
  return *this;
}

Object& Object::resize(const int& border_type) {
  self_data.border = border_type;
  refresh();
  terminal_manager::update(self_id, self_data);
  return *this;
}

Object& Object::change_text_color(const int& color) {
  self_data.text_color = color;
  refresh();
  terminal_manager::update(self_id, self_data);
  return *this;
}

Object& Object::change_fill_color(const int& color) {
  self_data.fill_color = color;
  refresh();
  terminal_manager::update(self_id, self_data);
  return *this;
}

Object& Object::change_text_color(const std::string& color) {
  self_data.text_color = convert_color_name(color, true);
  refresh();
  terminal_manager::update(self_id, self_data);
  return *this;
}

Object& Object::change_fill_color(const std::string& color) {
  self_data.fill_color = convert_color_name(color, false);
  refresh();
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

void Object::refresh() {
  text_size();
  if (terminal_manager::is_showing(self_id)) hide();
  show();
}

int Object::show_border() {
  if (terminal_manager::obj_border(self_id) == 0) return 0;

  if (terminal_manager::obj_border(self_id) != 1) return -1;

  int top = terminal_manager::obj_x(self_id);
  int left = terminal_manager::obj_y(self_id);
  int bottom = top + terminal_manager::obj_height(self_id);
  int right = left + terminal_manager::obj_width(self_id);

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

}  // namespace terminal
