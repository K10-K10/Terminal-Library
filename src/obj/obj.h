#pragma once

#ifndef TERMINAL_LIBRARY_OBJ_OBJ_H_
#define TERMINAL_LIBRARY_OBJ_OBJ_H_

#include <string>
#include <utility>

#include "field/field.h"
#include "obj/manager.h"

namespace terminal {
class Object {
  friend class Field;

 public:
  Object(const std::string& title, const std::string& text, const int row,
         const int col, const int height = 0, const int width = 0,
         const int border = 0);
  Object(const std::string& title, const std::string& text,
         const std::pair<int, int>& position,
         const std::pair<int, int>& size = {0, 0}, const int border = 0);
  Object& operator=(const std::string& new_text);
  // 0-show,1-x,2-y,3-height,4-width,5-text_width,6-text_height,7-text_color,8-fill_color,9-border,flags...
  int operator[](const int& num);
  std::string operator()(const int& type = 0);
  ~Object();

  Object& clear();

  Object& show();
  Object& hide();

  Object& move(const int& new_row, const int& new_col);
  Object& resize(const int& new_height, const int& new_width,
                 const int& border_type);
  Object& resize(const int& border_type);

  Object& change_text_color(const int& color);
  Object& change_fill_color(const int& color);
  Object& change_text_color(const std::string& color);
  Object& change_fill_color(const std::string& color);

 private:
  inline static int cnt = 0;
  int self_id;
  int convert_color_name(const std::string& name, const bool& is_text);
};

}  // namespace terminal

#endif  // TERMINAL_LIBRARY_OBJ_OBJ_H_
