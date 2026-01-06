#include "obj/manager.h"

#include <atomic>
#include <map>

#include "obj/obj.h"

namespace terminal {  // namespace terminal
class Object;
}  // namespace terminal

namespace terminal_manager {
void obj_drowing(std::atomic<bool>& running) {
  while (running) {
    for (const auto& pair : obj_map) {
      terminal::Object* obj_id = pair.first;
      ObjData obj_data = pair.second;
      if (obj_data.show) {
        obj_id->show();
      }
    }
    // Sleep or yield to avoid busy waiting
  }
}
}  // namespace terminal_manager
