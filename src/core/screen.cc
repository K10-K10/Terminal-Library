#include "core/screen.h"

#include <vector>

namespace __terminal__ {
void Screen::clear(int x, int y) {
  width = x;
  height = y;
  current.resize(x * y);
  next.resize(x * y);
}

void Screen::put(int x, int y, Cell c) { current[y * height + width] = c; }

void Screen::resize(int x, int y) {
  current.clear();
  next.clear();
  current.resize(x * y);
  next.resize(x * y);
  return;
}

}  // namespace __terminal__
