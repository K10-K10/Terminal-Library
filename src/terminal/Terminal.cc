#include "terminal/Terminal.h"

#include <iostream>

#include "obj/render.h"
#include "utils/base.h"

namespace terminal {

void Terminal::init() {
  std::cout << "\x1b[?1049h" << std::flush;
  terminal_manager::render::start();
}

void Terminal::init(int fps) {
  std::cout << "\x1b[?1049h" << std::flush;
  terminal_manager::render::start(fps);
}

void Terminal::shutdown() {
  terminal_manager::render::stop();
  terminal::utils::clear();
  std::cout << "\x1b[?1049l" << std::flush;
}

}  // namespace terminal
