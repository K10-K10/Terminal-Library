#pragma once

#ifndef TERMINAL_LIBRARY_OBJ_RENDER_H_
#define TERMINAL_LIBRARY_OBJ_RENDER_H_

#include "obj/manager.h"
#include "obj/obj.h"

namespace terminal {
class Object;
}  // namespace terminal
namespace terminal_manager {
class Render {
  friend class terminal_manager;

 private:
  static void render_object(terminal::Object* obj, const ObjData& data);
};
}  // namespace terminal_manager

#endif  // TERMINAL_LIBRARY_OBJ_RENDER_H_
