#include "obj/render.h"

#include <atomic>
#include <iostream>
#include <mutex>
#include <thread>
#include <utility>

#include "obj/manager.h"
#include "utils/base.h"

namespace terminal_manager::render {
namespace detail {
void draw_title(const int obj);
void draw_text(const int obj, const std::pair<int, int>& text_size);
void draw_border(const int obj, const std::pair<int, int>& text_size);
std::pair<int, int> cnt_text_size(const int obj);
}  // namespace detail

using terminal_manager::obj_mutex;
static std::atomic<bool> running{false};
static std::thread draw_thread;

static void obj_drawing(int fps) {
  using namespace std::chrono_literals;
  if (fps <= 0) fps = 60;
  auto frame_time = std::chrono::milliseconds(1000 / fps);
  while (running.load(std::memory_order_relaxed)) {
    {
      terminal::utils::clear();
      for (const auto& [id, data] : obj_map) {
        if (!data.show) continue;
        auto text_size = detail::cnt_text_size(id);
        detail::draw_border(id, text_size);
        detail::draw_title(id);
        detail::draw_text(id, text_size);
      }
    }
    constexpr auto fps_s = 16ms;
    std::this_thread::sleep_for(frame_time);
  }
}

void start(int fps) {
  if (running.exchange(true)) return;
  draw_thread = std::thread(obj_drawing, fps);
}

void stop() {
  running.store(false);
  if (draw_thread.joinable()) draw_thread.join();
}

namespace detail {
void draw_title(const int obj) {
  const auto& title = terminal_manager::get_title(obj);
  if (title.empty()) return;
  int row = terminal_manager::get_y(obj);
  int col = terminal_manager::get_x(obj) + 2;
  terminal::utils::MoveTo(row, col);
  for (size_t i = 0;
       i < std::min(title.size(),
                    static_cast<size_t>(terminal_manager::get_width(obj) - 2));
       ++i) {
    std::cout << title[i];
  }
}

void draw_text(const int obj, const std::pair<int, int>&) {
  int start_row = terminal_manager::get_y(obj) + 1;
  int start_col = terminal_manager::get_x(obj) + 1;
  int row = start_row;
  size_t pos = 0;
  const auto& text = terminal_manager::get_text(obj);
  while (row <
         terminal_manager::get_y(obj) + terminal_manager::get_height(obj) - 1) {
    size_t end = text.find('\n', pos);
    std::string line = (end == std::string::npos) ? text.substr(pos)
                                                  : text.substr(pos, end - pos);
    terminal::utils::MoveTo(row, start_col);
    std::cout << line.substr(0, terminal_manager::get_width(obj) - 2);

    if (end == std::string::npos) break;
    pos = end + 1;
    row++;
  }
}

void draw_border(const int obj, const std::pair<int, int>& text_size) {
  // Implementation for drawing border
  if (terminal_manager::get_border(obj) == 0) return;
  if (terminal_manager::get_border(obj) != 1) return;

  int top = terminal_manager::get_y(obj);
  int left = terminal_manager::get_x(obj);
  int bottom = top + terminal_manager::get_height(obj);
  int right = left + terminal_manager::get_width(obj);

  // ┌───┐
  terminal::utils::MoveTo(top, left);
  std::cout << "┌";
  for (int c = left + 1; c < right - 1; ++c) std::cout << "─";
  std::cout << "┐";

  // │   │
  for (int r = top + 1; r < bottom - 1; ++r) {
    terminal::utils::MoveTo(r, left);
    std::cout << "│";
    terminal::utils::MoveTo(r, right - 1);
    std::cout << "│";
  }

  // └───┘
  terminal::utils::MoveTo(bottom - 1, left);
  std::cout << "└";
  for (int c = left + 1; c < right - 1; ++c) std::cout << "─";
  std::cout << "┘";

  std::cout << std::flush;
  return;
}
std::pair<int, int> cnt_text_size(const int obj) {
  // Implementation for counting text size
  std::pair<int, int> size = {1, 0};

  int current_text_width = 0;
  auto it = obj_map.find(obj);
  if (it == obj_map.end()) return {0, 0};

  for (char c : it->second.text) {
    if (c == '\n') {
      size.first++;
      size.second = std::max(size.second, current_text_width);
      current_text_width = 0;
    } else {
      current_text_width++;
    }
  }
  size.second = std::max(size.second, current_text_width);
  return size;
}
}  // namespace detail
}  // namespace terminal_manager::render
