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

inline std::mutex obj_mutex;

extern std::atomic<bool> running;
extern std::thread draw_thread;

inline int selected_obj_id = -1;

void register_object(terminal::Object* obj, const ObjData& data);
void update(const terminal::Object* obj, const ObjData& data);
void unregister_object(terminal::Object* obj);

inline std::map<terminal::Object*, ObjData> obj_map;

int obj_generation(terminal::Object* obj);
int obj_x(terminal::Object* obj);
int obj_y(terminal::Object* obj);
int obj_width(terminal::Object* obj);
int obj_height(terminal::Object* obj);
bool is_showing(const terminal::Object* obj);
std::string obj_title(const terminal::Object* obj);
std::string obj_text(const terminal::Object* obj);
int obj_text_color(const terminal::Object* obj);
int obj_fill_color(const terminal::Object* obj);
int obj_border(const terminal::Object* obj);
int obj_flags(const terminal::Object* obj);

}  // namespace terminal_manager

#endif  // TERMINAL_LIBRARY_OBJ_MANAGER_H_
