#include "terminal/Terminal.h"

#include "obj/render.h"
#include "utils/base.h"

namespace terminal {

void Terminal::init() {
  utils::clear();
  terminal_manager::render::start();
}

void Terminal::shutdown() { terminal_manager::render::stop(); }

}  // namespace terminal
