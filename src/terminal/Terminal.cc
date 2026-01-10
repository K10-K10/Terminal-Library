#include "terminal/Terminal.h"

#include "obj/render.h"
#include "utils/base.h"

namespace terminal {

void Terminal::init() {
  utils::clear();
  terminal_manager::render::start();
}

void Terminal::init(int fps) {
  utils::clear();
  terminal_manager::render::start(fps);
}

void Terminal::shutdown() { terminal_manager::render::stop(); }

}  // namespace terminal
