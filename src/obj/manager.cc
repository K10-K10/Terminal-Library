#include "obj/manager.h"

#include <atomic>
#include <chrono>
#include <map>
#include <mutex>
#include <thread>

#include "obj/obj.h"

namespace terminal {  // namespace terminal
class Object;
}  // namespace terminal

namespace terminal_manager {
std::atomic<bool> running{false};
std::thread draw_thread;

void obj_drawing(std::atomic<bool>& running) {
  using namespace std::chrono_literals;

  while (running.load(std::memory_order_relaxed)) {
    {
      std::lock_guard<std::mutex> lock(obj_mutex);
      for (const auto& [obj, data] : obj_map) {
        if (data.show) {
          obj->show();
        } else {
          obj->hide();
        }
      }
    }
    std::this_thread::sleep_for(16ms);
  }
}

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

}  // namespace terminal_manager
