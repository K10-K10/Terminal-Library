#include "field/field.h"

#include <iostream>
#include <map>
#include <string>

#include "obj/render.h"

namespace terminal {
Field& Field::operator[](terminal::Object& obj) {
  field_map[id] = &obj;
  ++id;
  return *this;
}

Field Field::operator()() { return *this; }

void Field::init() {
  terminal_manager::running.store(true);

  terminal_manager::draw_thread =
      std::thread(terminal_manager::Render::obj_drawing,
                  std::ref(terminal_manager::running));
}

void Field::exit() {
  hide();
  terminal_manager::running.store(false);
  if (terminal_manager::draw_thread.joinable())
    terminal_manager::draw_thread.join();
}

void Field::show() {
  for (const auto& pair : field_map) {
    Object* obj = pair.second;
    terminal_manager::obj_map[obj].show = true;
  }
}

void Field::hide() {  // TODO(K10-K10): doesn't work
  for (const auto& pair : field_map) {
    Object* obj = pair.second;
    terminal_manager::obj_map[obj].show = false;
  }
}

Field::~Field() { std::cout << std::endl; }
}  // namespace terminal
