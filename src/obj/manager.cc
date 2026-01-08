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

void register_object(terminal::Object* obj, const ObjData& data) {
  std::lock_guard<std::mutex> lock(obj_mutex);
  obj_map[obj] = data;
}

void update(const terminal::Object* obj, const ObjData& data) {
  std::lock_guard<std::mutex> lock(obj_mutex);
  obj_map[const_cast<terminal::Object*>(obj)] = data;
}

void unregister_object(terminal::Object* obj) {
  std::lock_guard<std::mutex> lock(obj_mutex);
  obj_map.erase(obj);
}

int obj_generation(terminal::Object* obj) {
  std::lock_guard<std::mutex> lock(obj_mutex);
  return obj_map[obj].gen;
}

int obj_x(terminal::Object* obj) {
  std::lock_guard<std::mutex> lock(obj_mutex);
  return obj_map[obj].x;
}

int obj_y(terminal::Object* obj) {
  std::lock_guard<std::mutex> lock(obj_mutex);
  return obj_map[obj].y;
}
int obj_width(terminal::Object* obj) {
  std::lock_guard<std::mutex> lock(obj_mutex);
  return obj_map[obj].w;
}

int obj_height(terminal::Object* obj) {
  std::lock_guard<std::mutex> lock(obj_mutex);
  return obj_map[obj].h;
}

bool is_showing(const terminal::Object* obj) {
  std::lock_guard<std::mutex> lock(obj_mutex);
  return obj_map.at(const_cast<terminal::Object*>(obj)).show;
}

std::string obj_title(const terminal::Object* obj) {
  std::lock_guard<std::mutex> lock(obj_mutex);
  return obj_map.at(const_cast<terminal::Object*>(obj)).title;
}

std::string obj_text(const terminal::Object* obj) {
  std::lock_guard<std::mutex> lock(obj_mutex);
  return obj_map.at(const_cast<terminal::Object*>(obj)).text;
}

int obj_text_color(const terminal::Object* obj) {
  std::lock_guard<std::mutex> lock(obj_mutex);
  return obj_map.at(const_cast<terminal::Object*>(obj)).text_color;
}

int obj_fill_color(const terminal::Object* obj) {
  std::lock_guard<std::mutex> lock(obj_mutex);
  return obj_map.at(const_cast<terminal::Object*>(obj)).fill_color;
}

int obj_border(const terminal::Object* obj) {
  std::lock_guard<std::mutex> lock(obj_mutex);
  return obj_map.at(const_cast<terminal::Object*>(obj)).border;
}

int obj_flags(const terminal::Object* obj) {
  std::lock_guard<std::mutex> lock(obj_mutex);
  return obj_map.at(const_cast<terminal::Object*>(obj)).flags;
}

}  // namespace terminal_manager
