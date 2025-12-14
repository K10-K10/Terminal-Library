#pragma once

#ifndef TERMINAL_LIBRARY_FIELD_
#define TERMINAL_LIBRARY_FIELD_
#include <map>
#include <string>
#include <utility>

namespace terminal {
class Object {};

class field {
public:
  field();
  ~field();
  field operator[](terminal::Object); // Add object
  field operator()();
  void show();
  void hide();

private:
  std::map<int, int> field_map;
  int move_x, move_y;
};
} // namespace terminal

#endif
