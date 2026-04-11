#include "core/render.h"

#include <fstream>
#include <iostream>
#include <string>

#include "core/screen.h"
#include "utils/base.h"

namespace __terminal__ {
void Render::flush() {
  int W = terminal::screen.width();
  int H = terminal::screen.height();
  int start = -1;
  std::string line;
  for (int y = 0; y < H; ++y) {
    start = -1;
    line.clear();
    for (int x = 0; x < W; ++x) {
      int i = y * W + x;

      if (terminal::screen.current[i].c != terminal::screen.next[i].c) {
        if (start == -1) {
          start = x;
          line.clear();
        }

        line += terminal::screen.next[i].c;
        terminal::screen.current[i] = terminal::screen.next[i];
      } else if (start != -1) {
        terminal::utils::moveTo(y, start);
        std::cout << line;
        start = -1;
        line.clear();
      }
    }
    if (start != -1) {
      terminal::utils::moveTo(y, start);
      std::cout << line << std::flush;
      start = -1;
      line.clear();
    }
  }
  terminal::screen.current = terminal::screen.next;
  terminal::screen.next.clear();
  std::cout << std::flush;
}

Render render;

}  // namespace __terminal__
