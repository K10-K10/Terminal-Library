#include <vector>

namespace terminal {
class Object;
}

namespace __terminal__ {
struct Cell {
  char c;
  int fg = -1, bg = -1;
};

class App;
class Render;
class Screen {
  friend App;
  friend Render;

 public:
  int width() const;
  int height() const;

 private:
  void clear(int x, int y);
  void put(int x, int y, Cell c);
  void resize(int x, int y);

  std::vector<Cell> current, next;
  int width_, height_;
};

}  // namespace __terminal__

namespace terminal {
extern __terminal__::Screen screen;
}
