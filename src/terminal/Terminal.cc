#include "terminal/Terminal.h"

#include <csignal>
#include <iostream>

#include "obj/render.h"
#include "utils/base.h"
#include "utils/internal.h"
namespace {
void handler(int signum) { _terminal_manager::sig_flag = signum; }
}  // namespace

namespace terminal {
void Terminal::init() {
  signal(SIGWINCH, handler);
  signal(SIGINT, handler);
  std::cout << "\x1b[?1049h" << std::flush;
  _terminal_manager::render::start();
}

void Terminal::init(int fps) {
  signal(SIGWINCH, handler);
  std::cout << "\x1b[?1049h" << std::flush;
  _terminal_manager::render::start(fps);
}

void Terminal::shutdown() {
  _terminal_manager::render::stop();
  terminal::utils::clear();
  std::cout << "\x1b[?1049l" << std::flush;
  std::cout << std::flush;
}

}  // namespace terminal
