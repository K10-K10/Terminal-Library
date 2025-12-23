#include "field/field.h"

#include <iostream>
#include <map>
#include <string>

namespace terminal {
Field& Field::operator[](terminal::Object& obj) {
  field_map[obj.self_id] = id++;
  return *this;
}
Field Field::operator()() { return *this; }
Field::~Field() { std::cout << std::endl; }
}  // namespace terminal
