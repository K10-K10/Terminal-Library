#include "terminal/Terminal.h"

#include "obj/render.h"
#include "utils/base.h"

namespace terminal {

void App::init() {
  terminal_manager::render::start();
  utils::InitCursor();
}

void App::shutdown() { terminal_manager::render::stop(); }

}  // namespace terminal
