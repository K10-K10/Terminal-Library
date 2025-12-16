#include "./field.hpp"

namespace terminal {
class field {
public:
  field();
  ~field();
  field &operator[](terminal::Object &obj) {
    field_map[obj.self_id] = id++;
    return *this;
  }

private:
  int id = 0;
  std::map<int, int> field_map;
  int move_x, move_y;
};
} // namespace terminal
