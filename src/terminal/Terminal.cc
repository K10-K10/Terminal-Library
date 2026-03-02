#include "terminal/Terminal.h"

#include <csignal>
#include <iostream>

#include "obj/render.h"
#include "utils/base.h"
namespace {
void handler(int signum) { __terminal__::__manager__::sig_flag = signum; }
}  // namespace

namespace __terminal__ {
void Terminal::init() {
  signal(SIGWINCH, handler);
  signal(SIGINT, handler);
  std::cout << "\x1b[?1049h" << std::flush;
  __terminal__::__manager__::__render__::start();
}

void Terminal::init(int fps) {
  signal(SIGWINCH, handler);
  std::cout << "\x1b[?1049h" << std::flush;
  __terminal__::__manager__::__render__::start(fps);
}

void Terminal::shutdown() {
  __terminal__::__manager__::__render__::stop();
  terminal::utils::clear();
  std::cout << "\x1b[?25h";
  std::cout << "\x1b[?1049l" << std::flush;
}

}  // namespace __terminal__

namespace terminal {
__terminal__::Terminal Terminal;
}  // namespace terminal
