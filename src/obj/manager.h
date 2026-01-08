#pragma once

#ifndef TERMINAL_LIBRARY_OBJ_MANAGER_H_
#define TERMINAL_LIBRARY_OBJ_MANAGER_H_

#include <atomic>
#include <map>
#include <mutex>
#include <string>
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
  std::string title;
  std::string text;
  int text_color = -1;
  int fill_color = -1;
  int border = 0;
  // 0-italic 1-under 2-text_width
  int flags = 0;
};

extern std::atomic<bool> running;
extern std::thread draw_thread;

inline int selected_obj_id = -1;

void register_object(int id, const ObjData& data);
void update(const int id, const ObjData& data);
void unregister_object(int id);

inline std::mutex obj_mutex;
inline std::atomic<bool> running{false};
inline std::thread draw_thread;
inline std::map<int, ObjData> obj_map;

const int obj_generation(int id);
const int obj_x(int id);
const int obj_y(int id);
const int obj_width(int id);
const int obj_height(int id);
const bool is_showing(const int id);
const std::string obj_title(const int id);
const std::string obj_text(const int id);
const int obj_text_color(const int id);
const int obj_fill_color(const int id);
const int obj_border(const int id);
const int obj_flags(const int id);

}  // namespace terminal_manager

#endif  // TERMINAL_LIBRARY_OBJ_MANAGER_H_
