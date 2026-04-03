#include "obj/block.h"

#include "obj/obj.h"

namespace terminal {
Block& Block::set_type(int new_type) {
  Block::type_ = new_type;
  return *this;
}

int Block::get_type() { return type_; }

void Block::draw(Screen& s, const Rect& r) {}

}  // namespace terminal
