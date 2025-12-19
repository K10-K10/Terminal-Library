#pragma once

#ifndef TERMINAL_LIBRARY_FIELD_FIELD_H_
#define TERMINAL_LIBRARY_FIELD_FIELD_H_

#include "../obj/obj.h"

#include <map>
#include <string>
#include <utility>

namespace terminal {
class Object;
class Field {
public:
  Field() = default;
  ~Field() = default;
  Field &operator[](Object &); // Add object
  Field operator()();
  void show();
  void hide();

private:
  int id = 0;
  std::map<int, int> field_map;
  int move_x, move_y;
};
} // namespace terminal

#endif // TERMINAL_LIBRARY_FIELD_FIELD_H_
