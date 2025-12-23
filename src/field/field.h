#pragma once

#ifndef TERMINAL_LIBRARY_FIELD_FIELD_H_
#define TERMINAL_LIBRARY_FIELD_FIELD_H_

#include <map>
#include <string>

#include "obj/obj.h"

namespace terminal {
class Object;
class Field {
 public:
  Field() = default;
  Field& operator[](Object&);  // Add object
  Field operator()();
  ~Field();
  void show();
  void hide();

 private:
  int id = 0;
  std::map<int, int> field_map;  // Map of object IDs to field IDs
  int move_x, move_y;
};
}  // namespace terminal

#endif  // TERMINAL_LIBRARY_FIELD_FIELD_H_
