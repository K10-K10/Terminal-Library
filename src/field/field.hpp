#pragma once

#ifndef TERMINAL_LIBRARY_FIELD_
#define TERMINAL_LIBRARY_FIELD_
#include "../obj/obj.hpp"
#include <map>
#include <string>
#include <utility>

namespace terminal {
class field {
public:
  field();
  ~field();
  // field operator[](terminal::Object); // Add object
  field operator()();
  void show();
  void hide();

private:
  std::map<int, int> field_map;
  int move_x, move_y;
};
} // namespace terminal

#endif
