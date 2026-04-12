#include "core/screen.h"

#include <vector>

namespace __terminal__ {

int Screen::width() const { return width_; }
int Screen::height() const { return height_; }

void Screen::resize(int w, int h) {
  width_ = w;
  height_ = h;
  current.assign(w * h, {" "});
  next.assign(w * h, {" "});
}

void Screen::clear() { std::fill(next.begin(), next.end(), Cell{" "}); }

void Screen::put(int x, int y, Cell c) { next[y * width_ + x] = c; }

__terminal__::Screen screen;

}  // namespace __terminal__
