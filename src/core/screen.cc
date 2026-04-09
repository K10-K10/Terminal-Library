#include "core/screen.h"

#include <vector>

namespace __terminal__ {

int Screen::width() const { return width_; }
int Screen::height() const { return height_; }

void Screen::clear(int x, int y) {
  width_ = x;
  height_ = y;
  current.resize(x * y);
  next.resize(x * y);
}

void Screen::put(int x, int y, Cell c) { current[y * width_ + x] = c; }

void Screen::resize(int x, int y) {
  width_ = x;
  height_ = y;
  current.clear();
  next.clear();
  current.resize(x * y);
  next.resize(x * y);
}

}  // namespace __terminal__

namespace terminal {
__terminal__::Screen screen;
}
