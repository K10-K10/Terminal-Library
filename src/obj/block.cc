#include "obj/block.h"

#include "core/drawObj.h"
#include "layout/rect.h"

namespace terminal {
Block& Block::set_pos(const Rect& r) {
  rect = r;
  return *this;
}

Block& Block::set_type(int new_type) {
  Block::type_ = new_type;
  return *this;
}

int Block::get_type() { return type_; }

void Block::draw() {
  __terminal__::drawObj.put(rect.y, rect.x, {single.tl});
  __terminal__::drawObj.put(rect.y, rect.right(), {single.tr});
  __terminal__::drawObj.put(rect.bottom(), rect.x, {single.bl});
  __terminal__::drawObj.put(rect.bottom(), rect.right(), {single.br});
  for (int x = rect.x + 1; x < rect.right(); ++x) {
    __terminal__::drawObj.put(rect.y, x, {single.h});
    __terminal__::drawObj.put(rect.bottom(), x, {single.h});
  }
  for (int y = rect.y + 1; y < rect.bottom(); ++y) {
    __terminal__::drawObj.put(y, rect.x, {single.v});
    __terminal__::drawObj.put(y, rect.right(), {single.v});
  }
}

}  // namespace terminal
