#pragma once

#ifndef TERMINAL_LIBRARY_OBJ_MANAGER_H_
#define TERMINAL_LIBRARY_OBJ_MANAGER_H_

#include <atomic>
#include <map>
#include <mutex>
#include <string>
#include <thread>

namespace _terminal_manager {
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
void unregister_object(int id);

extern std::mutex obj_mutex;
extern std::map<int, ObjData> obj_map;

void set_x(int id, int x);
void set_y(int id, int y);
void set_width(int id, int width);
void set_height(int id, int height);
void set_show(int id, bool flag);
void set_title(int id, std::string title);
void set_text(int id, std::string text);
void set_text_color(int id, int value);
void set_fill_color(int id, int value);
void set_border(int id, int border);
void set_flags(int id, int flags);

const int get_generation(int id);
const int get_x(int id);
const int get_y(int id);
const int get_width(int id);
const int get_height(int id);
const bool get_showing(const int id);
const std::string get_title(const int id);
const std::string get_text(const int id);
const int get_text_color(const int id);
const int get_fill_color(const int id);
const int get_border(const int id);
const int get_flags(const int id);
}  // namespace _terminal_manager

#endif  // TERMINAL_LIBRARY_OBJ_MANAGER_H_
