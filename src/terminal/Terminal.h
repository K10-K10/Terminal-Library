#pragma once
#ifndef TERMINAL_LIBRARY_TERMINAL_TERMINAL_H_
#define TERMINAL_LIBRARY_TERMINAL_TERMINAL_H_

namespace terminal {

class Terminal {
 public:
  static void init();
  static void shutdown();
};

}  // namespace terminal

#endif
