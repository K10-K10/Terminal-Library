#pragma once

#ifndef TERMINAL_LIBRARY_OBJ_MANAGER_H_
#define TERMINAL_LIBRARY_OBJ_MANAGER_H_

#include <atomic>
#include <map>
#include <mutex>
#include <thread>

namespace terminal {
class Object;
}  // namespace terminal
namespace terminal_manager {
struct ObjData {
  int gen;
  int x;
  int y;
  int w;
  int h;
  int show = false;
};

inline std::mutex obj_mutex;

extern std::atomic<bool> running;
extern std::thread draw_thread;

void obj_drawing(std::atomic<bool>& running);

inline int selected_obj_id = -1;

inline std::map<terminal::Object*, ObjData> obj_map;
}  // namespace terminal_manager

#endif  // TERMINAL_LIBRARY_OBJ_MANAGER_H_
