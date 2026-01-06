#pragma once

#ifndef TERMINAL_LIBRARY_OBJ_MANAGER_H_
#define TERMINAL_LIBRARY_OBJ_MANAGER_H_

#include <atomic>
#include <map>

namespace terminal_manager {
struct ObjData {
  int gen;
  int x;
  int y;
  int w;
  int h;
  int show = false;
};

inline int selected_obj_id = -1;

inline std::map<int, ObjData> obj_map;
}  // namespace terminal_manager

#endif  // TERMINAL_LIBRARY_OBJ_MANAGER_H_
