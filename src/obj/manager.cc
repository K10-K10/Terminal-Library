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
        }
      }
    }
    std::this_thread::sleep_for(16ms);
  }
}

}  // namespace terminal_manager
