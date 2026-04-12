#include "app/app.h"

#include <termios.h>
#include <unistd.h>

#include <chrono>
#include <csignal>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <thread>

#include "core/render.h"
#include "core/screen.h"
#include "utils/base.h"

namespace __terminal__ {
termios orig;

void enable_raw_mode() {
  tcgetattr(STDIN_FILENO, &orig);

  termios raw = orig;
  raw.c_lflag &= ~(ECHO | ICANON);

  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void disable_raw_mode() { tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig); }
int __terminal__::App::sig_num = 0;

App::App(Render& r) : render(r){};

void App::signal_handler(int sig) { sig_num = sig; }

void App::init(int arg_fps) {
  std::signal(SIGINT, App::signal_handler);
  std::signal(SIGWINCH, App::signal_handler);

  std::cout << "\x1b[?1049h" << std::flush;
  std::cout << "\x1b[?25l" << std::flush;
  enable_raw_mode();
  auto [height, width] = terminal::utils::getTerminalSize();
  __terminal__::screen.resize(width, height);
  fps = arg_fps;
}

void App::loop(std::function<void()> frame) {
  runnning = true;
  while (runnning) {
    if (sig_num == SIGWINCH) {
      auto [height, width] = terminal::utils::getTerminalSize();
      terminal::utils::clear();
      __terminal__::screen.resize(width, height);
      sig_num = 0;
    }
    if (sig_num == SIGINT) {
      stop();
      std::exit(0);
    }
    frame();
    render.flush();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
  }
}

void App::stop() {
  runnning = false;
  std::cout << "\x1b[?1049l" << std::flush;
  std::cout << "\x1b[?25h" << std::flush;
  disable_raw_mode();
  return;
}

}  // namespace __terminal__
