#include "obj/manager.h"

#include <map>
#include <mutex>
#include <string>

namespace terminal_manager {

// =====================
// globals
// =====================
std::mutex obj_mutex;
std::map<int, ObjData> obj_map;

// =====================
// internal helper
// =====================
static ObjData* find_obj(int id) {
  auto it = obj_map.find(id);
  if (it == obj_map.end()) return nullptr;
  return &it->second;
}

// =====================
// register / unregister
// =====================
void register_object(int id, const ObjData& data) {
  std::lock_guard<std::mutex> lock(obj_mutex);
  obj_map[id] = data;
}

void unregister_object(int id) {
  std::lock_guard<std::mutex> lock(obj_mutex);
  obj_map.erase(id);
}

// =====================
// setters
// =====================
void set_x(int id, int x) {
  std::lock_guard<std::mutex> lock(obj_mutex);
  if (auto* o = find_obj(id)) {
    o->x = x;
    o->gen++;
  }
}

void set_y(int id, int y) {
  std::lock_guard<std::mutex> lock(obj_mutex);
  if (auto* o = find_obj(id)) {
    o->y = y;
    o->gen++;
  }
}

void set_width(int id, int width) {
  std::lock_guard<std::mutex> lock(obj_mutex);
  if (auto* o = find_obj(id)) {
    o->w = width;
    o->gen++;
  }
}

void set_height(int id, int height) {
  std::lock_guard<std::mutex> lock(obj_mutex);
  if (auto* o = find_obj(id)) {
    o->h = height;
    o->gen++;
  }
}

void set_show(int id, bool flag) {
  std::lock_guard<std::mutex> lock(obj_mutex);
  if (auto* o = find_obj(id)) {
    o->show = flag;
    o->gen++;
  }
}

void set_title(int id, std::string title) {
  std::lock_guard<std::mutex> lock(obj_mutex);
  if (auto* o = find_obj(id)) {
    o->title = std::move(title);
    o->gen++;
  }
}

void set_text(int id, std::string text) {
  std::lock_guard<std::mutex> lock(obj_mutex);
  if (auto* o = find_obj(id)) {
    o->text = std::move(text);
    o->gen++;
  }
}

void set_text_color(int id, int value) {
  std::lock_guard<std::mutex> lock(obj_mutex);
  if (auto* o = find_obj(id)) {
    o->text_color = value;
    o->gen++;
  }
}

void set_fill_color(int id, int value) {
  std::lock_guard<std::mutex> lock(obj_mutex);
  if (auto* o = find_obj(id)) {
    o->fill_color = value;
    o->gen++;
  }
}

void set_border(int id, int border) {
  std::lock_guard<std::mutex> lock(obj_mutex);
  if (auto* o = find_obj(id)) {
    o->border = border;
    o->gen++;
  }
}

void set_flags(int id, int flags) {
  std::lock_guard<std::mutex> lock(obj_mutex);
  if (auto* o = find_obj(id)) {
    o->flags = flags;
    o->gen++;
  }
}

// =====================
// getters
// =====================
const int get_generation(int id) {
  std::lock_guard<std::mutex> lock(obj_mutex);
  if (auto* o = find_obj(id)) return o->gen;
  return 0;
}

const int get_x(int id) {
  std::lock_guard<std::mutex> lock(obj_mutex);
  if (auto* o = find_obj(id)) return o->x;
  return 0;
}

const int get_y(int id) {
  std::lock_guard<std::mutex> lock(obj_mutex);
  if (auto* o = find_obj(id)) return o->y;
  return 0;
}

const int get_width(int id) {
  std::lock_guard<std::mutex> lock(obj_mutex);
  if (auto* o = find_obj(id)) return o->w;
  return 0;
}

const int get_height(int id) {
  std::lock_guard<std::mutex> lock(obj_mutex);
  if (auto* o = find_obj(id)) return o->h;
  return 0;
}

const bool get_showing(int id) {
  std::lock_guard<std::mutex> lock(obj_mutex);
  if (auto* o = find_obj(id)) return o->show;
  return false;
}

const std::string get_title(int id) {
  std::lock_guard<std::mutex> lock(obj_mutex);
  if (auto* o = find_obj(id)) return o->title;
  return "";
}

const std::string get_text(int id) {
  std::lock_guard<std::mutex> lock(obj_mutex);
  if (auto* o = find_obj(id)) return o->text;
  return "";
}

const int get_text_color(int id) {
  std::lock_guard<std::mutex> lock(obj_mutex);
  if (auto* o = find_obj(id)) return o->text_color;
  return -1;
}

const int get_fill_color(int id) {
  std::lock_guard<std::mutex> lock(obj_mutex);
  if (auto* o = find_obj(id)) return o->fill_color;
  return -1;
}

const int get_border(int id) {
  std::lock_guard<std::mutex> lock(obj_mutex);
  if (auto* o = find_obj(id)) return o->border;
  return 0;
}

const int get_flags(int id) {
  std::lock_guard<std::mutex> lock(obj_mutex);
  if (auto* o = find_obj(id)) return o->flags;
  return 0;
}

}  // namespace terminal_manager
