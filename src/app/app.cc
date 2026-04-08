#include "app/app.h"

#include <csignal>
#include <functional>
#include <iostream>

#include "core/render.h"
#include "core/screen.h"
#include "utils/base.h"

namespace __terminal__ {
void App::signal_handler(int sig) { sig_num = sig; }

void App::init(int arg_fps) {
  std::signal(SIGINT, App::signal_handler);
  std::signal(SIGWINCH, App::signal_handler);

  std::cout << "\x1b[?1049h" << std::flush;
  auto [height, width] = terminal::utils::getTerminalSize();
  fps = arg_fps;
  terminal::screen.clear(width, height);
}

void App::loop(std::function<void()> frame) {
  runnning = true;
  while (runnning) {
    if (sig_num == SIGWINCH) {
      auto [height, width] = terminal::utils::getTerminalSize();
      terminal::utils::clear();
      terminal::screen.resize(width, height);  // TODO: Object Resize
      sig_num = 0;
    }
    if (sig_num == SIGINT) {
      stop();
    }
    frame;
    render.flush();
  }
}

void App::stop() {
  runnning = false;
  std::cout << "\x1b[?1049l" << std::flush;
  return;
}

}  // namespace __terminal__
