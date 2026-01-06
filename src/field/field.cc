#include "field/field.h"

#include <iostream>
#include <map>
#include <string>

namespace terminal {
Field& Field::operator[](terminal::Object& obj) {
  field_map[id] = &obj;
  ++id;
  return *this;
}

Field Field::operator()() { return *this; }

void Field::init() {
  terminal_manager::running.store(true);

  terminal_manager::draw_thread = std::thread(
      terminal_manager::obj_drawing, std::ref(terminal_manager::running));
}

void Field::exit() { hide(); }

void Field::show() {
  for (const auto& pair : field_map) {
    Object* obj = pair.second;
    terminal_manager::obj_map[obj].show = true;
  }
}

void Field::hide() {
  for (const auto& pair : field_map) {
    Object* obj = pair.second;
    terminal_manager::obj_map[obj].show = false;
  }
}

Field::~Field() { std::cout << std::endl; }
}  // namespace terminal
