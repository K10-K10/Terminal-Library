#include "terminal/Terminal.h"

#include "obj/render.h"
#include "utils/base.h"

namespace terminal {

void Terminal::init() {
  terminal_manager::render::start();
  utils::InitCursor();
}

void Terminal::shutdown() { terminal_manager::render::stop(); }

}  // namespace terminal
