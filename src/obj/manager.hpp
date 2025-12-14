#pragma once

#ifndef TERMINAL_LIBRARY_MANAGER_
#define TERMINAL_LIBRARY_MANAGER

#include <map>

namespace terminal_manager {
struct obj_data {
  int gen;
  int x;
  int y;
  int w;
  int h;
  int show;
};

std::map<int, obj_data> obj_map;
} // namespace terminal_manager

#endif
