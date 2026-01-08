#include "field/field.h"

#include <iostream>
#include <map>
#include <string>

#include "obj/render.h"

namespace terminal {
Field& Field::operator[](terminal::Object& obj) {
  field_map[id] = obj.self_id;
  ++id;
  return *this;
}

Field Field::operator()() { return *this; }

void Field::init() { terminal_manager::render::start(); }

void Field::exit() {
  hide();
  terminal_manager::render::stop();
}

void Field::show() {
  for (const auto& pair : field_map) {
    int obj = pair.second;
    terminal_manager::obj_map[obj].show = true;
  }
}

void Field::hide() {  // TODO(K10-K10): doesn't work
  for (const auto& pair : field_map) {
    int obj = pair.second;
    terminal_manager::obj_map[obj].show = false;
  }
}

Field::~Field() { std::cout << std::endl; }
}  // namespace terminal
