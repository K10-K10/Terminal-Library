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
  void init();
  void exit();
  void show();
  void hide();
  ~Field();

 private:
  int id = 0;
  std::map<int, Object*> field_map;  // Map of object IDs to field IDs
  int move_x, move_y;
  int selected_id = -1;
};
}  // namespace terminal

#endif  // TERMINAL_LIBRARY_FIELD_FIELD_H_
