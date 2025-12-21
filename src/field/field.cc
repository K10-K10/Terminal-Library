#include "field/field.h"

#include <map>
#include <string>

namespace terminal {
class Field {
 public:
  Field();
  Field& Field::operator[](terminal::Object& obj) {
    field_map[obj.self_id] = id++;
    return *this;
  }
  ~Field();
  Field Field::operator()() { return *this; }

 private:
  int id = 0;
  std::map<int, int> field_map;
  int move_x, move_y;
};
}  // namespace terminal
