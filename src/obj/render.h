#pragma once

#ifndef TERMINAL_LIBRARY_OBJ_RENDER_H_
#define TERMINAL_LIBRARY_OBJ_RENDER_H_

#include <utility>

#include "obj/manager.h"

namespace terminal {
class Object;
class Field;
}  // namespace terminal
namespace terminal_manager::render {

void start();
void stop();
static void obj_drawing();

namespace detail {
void draw_text(const int obj, const std::pair<int, int>& text_size);
void draw_title(const int obj);
void draw_border(const int obj, const std::pair<int, int>& text_size);
std::pair<int, int> cnt_text_size(const int obj);
}  // namespace detail
}  // namespace terminal_manager::render

#endif  // TERMINAL_LIBRARY_OBJ_RENDER_H_
