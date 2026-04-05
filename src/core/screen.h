#include <vector>

#include "core/render.h"

namespace __terminal__ {
struct Cell {
  char c;
  int fg = -1, bg = -1;
};
class Screen {
  friend Render;

 public:
  void clear(int x, int y);
  void put(int x, int y, Cell c);
  void resize(int x, int y);

 protected:
  std::vector<Cell> current, next;
  int width, height;
};

Screen screen;

}  // namespace __terminal__
