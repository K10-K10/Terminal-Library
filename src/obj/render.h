#pragma once

#ifndef TERMINAL_LIBRARY_OBJ_RENDER_H_
#define TERMINAL_LIBRARY_OBJ_RENDER_H_

#include <utility>

#include "obj/manager.h"
namespace _terminal_manager::render {
void start(int fps = 60);
void stop();
static void obj_drawing(int fps);

namespace detail {
inline int terminal_row = 0;
inline int terminal_col = 0;
void draw_text(const int obj, const std::pair<int, int>& text_size);
void draw_title(const int obj);
void draw_border(const int obj, const std::pair<int, int>& text_size);
std::pair<int, int> cnt_text_size(const int obj);
}  // namespace detail
}  // namespace _terminal_manager::render

#endif  // TERMINAL_LIBRARY_OBJ_RENDER_H_
