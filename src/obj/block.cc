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
  if (rect.w < 2 || rect.h < 2) return;

  int l = rect.x;
  int r = rect.right();
  int t = rect.y;
  int b = rect.bottom();

  __terminal__::drawObj.put(t, l, {single.tl});
  __terminal__::drawObj.put(t, r, {single.tr});
  __terminal__::drawObj.put(b, l, {single.bl});
  __terminal__::drawObj.put(b, r, {single.br});

  for (int x = l + 1; x < r; ++x) {
    __terminal__::drawObj.put(t, x, {single.h});
    __terminal__::drawObj.put(b, x, {single.h});
  }

  for (int y = t + 1; y < b; ++y) {
    __terminal__::drawObj.put(y, l, {single.v});
    __terminal__::drawObj.put(y, r, {single.v});
  }
}

}  // namespace terminal
