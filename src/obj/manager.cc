#include "obj/manager.h"

#include <atomic>
#include <chrono>
#include <map>
#include <mutex>
#include <string>
#include <thread>

#include "obj/obj.h"

namespace terminal {  // namespace terminal
class Object;
}  // namespace terminal

namespace terminal_manager {

std::mutex obj_mutex;
std::map<int, ObjData> obj_map;

void register_object(int obj, const ObjData& data) {
  std::lock_guard<std::mutex> lock(obj_mutex);
  obj_map[obj] = data;
}

void update(const int obj, const ObjData& data) {
  std::lock_guard<std::mutex> lock(obj_mutex);
  obj_map[obj] = data;
}

void unregister_object(int obj) {
  std::lock_guard<std::mutex> lock(obj_mutex);
  obj_map.erase(obj);
}

const int obj_generation(int obj) {
  std::lock_guard<std::mutex> lock(obj_mutex);
  return obj_map[obj].gen;
}

const int obj_x(int obj) {
  std::lock_guard<std::mutex> lock(obj_mutex);
  return obj_map[obj].x;
}

const int obj_y(int obj) {
  std::lock_guard<std::mutex> lock(obj_mutex);
  return obj_map[obj].y;
}

const int obj_width(int obj) {
  std::lock_guard<std::mutex> lock(obj_mutex);
  return obj_map[obj].w;
}

const int obj_height(int obj) {
  std::lock_guard<std::mutex> lock(obj_mutex);
  return obj_map[obj].h;
}

const bool is_showing(const int obj) {
  std::lock_guard<std::mutex> lock(obj_mutex);
  return obj_map[obj].show;
}

const std::string obj_title(const int obj) {
  std::lock_guard<std::mutex> lock(obj_mutex);
  return obj_map[obj].title;
}

const std::string obj_text(const int obj) {
  std::lock_guard<std::mutex> lock(obj_mutex);
  return obj_map[obj].text;
}

const int obj_text_color(const int obj) {
  std::lock_guard<std::mutex> lock(obj_mutex);
  return obj_map[obj].text_color;
}

const int obj_fill_color(const int obj) {
  std::lock_guard<std::mutex> lock(obj_mutex);
  return obj_map[obj].fill_color;
}

const int obj_border(const int obj) {
  std::lock_guard<std::mutex> lock(obj_mutex);
  return obj_map[obj].border;
}

const int obj_flags(const int obj) {
  std::lock_guard<std::mutex> lock(obj_mutex);
  return obj_map[obj].flags;
}

}  // namespace terminal_manager
