#pragma once
#ifndef TERMINAL_LIBRARY_TERMINAL_TERMINAL_H_
#define TERMINAL_LIBRARY_TERMINAL_TERMINAL_H_

namespace __terminal__ {

class Terminal {
 public:
  static void init();
  static void init(int fps);
  static void shutdown();
};

}  // namespace __terminal__

namespace terminal {
extern __terminal__::Terminal Terminal;
}  // namespace terminal

#endif
