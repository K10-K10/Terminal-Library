#include "field/field.h"

#include <iostream>
#include <map>
#include <string>

#include "obj/manager.h"
#include "obj/render.h"

namespace terminal {
Field& Field::operator[](terminal::Object& obj) {
  field_map[id] = obj.self_id;
  return *this;
}

Field Field::operator()() { return *this; }

void Field::show() {
  for (const auto& [_, obj] : field_map) {
    _terminal_manager::set_show(obj, true);
  }
}

void Field::hide() {
  for (const auto& [_, obj] : field_map) {
    _terminal_manager::set_show(obj, false);
  }
}

Field::~Field() { std::cout << std::endl; }
}  // namespace terminal
