#include "obj/block.h"

#include "core/drawObj.h"
#include "layout/rect.h"

namespace terminal {
Block& Block::set_type(int new_type) {
  Block::type_ = new_type;
  return *this;
}

int Block::get_type() { return type_; }

void Block::draw(const Rect& r) {
  __terminal__::drawObj.put(r.y, r.x, {*single.tl});
  __terminal__::drawObj.put(r.y, r.right(), {*single.tr});
  __terminal__::drawObj.put(r.bottom(), r.x, {*single.bl});
  __terminal__::drawObj.put(r.bottom(), r.right(), {*single.br});
  for (int x = r.x + 1; x < r.right(); ++x) {
    __terminal__::drawObj.put(r.y, x, {*single.h});
    __terminal__::drawObj.put(r.bottom(), x, {*single.h});
  }
  for (int y = r.y + 1; y < r.bottom(); ++y) {
    __terminal__::drawObj.put(y, r.x, {*single.v});
    __terminal__::drawObj.put(y, r.right(), {*single.v});
  }
}

}  // namespace terminal
