#include "obj/render.h"

#include <atomic>
#include <iostream>
#include <mutex>
#include <thread>
#include <utility>

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

static void obj_drawing() {
  using namespace std::chrono_literals;
  std::cerr << "render tick, objects=" << obj_map.size() << "\n";
  while (running.load(std::memory_order_relaxed)) {
    {
      std::lock_guard<std::mutex> lock(obj_mutex);
      for (const auto& [id, data] : obj_map) {
        if (!data.show) continue;
        std::cerr << id << "\n";
        std::pair<int, int> text_size = detail::cnt_text_size(id);
        detail::draw_border(id, text_size);
        detail::draw_title(id);
        detail::draw_text(id, text_size);
      }
    }
    std::this_thread::sleep_for(16ms);
  }
}

void start() {
  if (running.exchange(true)) return;
  draw_thread = std::thread(obj_drawing);
}

void stop() {
  running.store(false);
  if (draw_thread.joinable()) draw_thread.join();
}

namespace detail {
void draw_title(const int obj) {
  // Implementation for drawing title
  if (terminal_manager::obj_title(obj).empty()) return;

  int title_start_col = terminal_manager::obj_y(obj) + 2;
  terminal::utils::MoveTo(terminal_manager::obj_x(obj), title_start_col);
  for (size_t i = 0;
       i < std::min(terminal_manager::obj_title(obj).size(),
                    static_cast<size_t>(terminal_manager::obj_width(obj) - 1));
       ++i) {
    std::cout << terminal_manager::obj_title(obj)[i];
  }
}

void draw_text(const int obj, const std::pair<int, int>& text_size) {
  // Implementation for drawing text
  if (terminal_manager::obj_flags(obj) & (1 << 0))  // Italic
    std::cout << "\e[3m";
  if (terminal_manager::obj_flags(obj) & (1 << 1))  // under_bar
    std::cout << "\e[4m";
  if (terminal_manager::obj_flags(obj) & (1 << 2))
    std::cout << "\e[1m";  // bold
  detail::cnt_text_size(obj);
  int text_start_col = terminal_manager::obj_x(obj) + 2;
  int text_start_row = terminal_manager::obj_y(obj) + 2;
  terminal::utils::MoveTo(text_start_col, text_start_row);
  int current_col = text_start_col;
  int current_row = text_start_row;
  size_t start = 0;
  while (true) {
    if (current_col >=
        terminal_manager::obj_x(obj) + terminal_manager::obj_height(obj) - 1)
      break;
    size_t end = terminal_manager::obj_text(obj).find('\n', start);
    std::string line =
        (end == std::string::npos)
            ? terminal_manager::obj_text(obj).substr(start)
            : terminal_manager::obj_text(obj).substr(start, end - start);
    std::cout << "\e[" << current_col << ";" << text_start_row << "H";
    if (terminal_manager::obj_text_color(obj) >= 0)
      std::cout << "\e[" << terminal_manager::obj_text_color(obj) << "m";
    if (terminal_manager::obj_fill_color(obj) >= 0)
      std::cout << "\e[" << terminal_manager::obj_fill_color(obj) << "m";
    std::cout << line.substr(0, terminal_manager::obj_width(obj) - 2);
    if (end == std::string::npos) break;
    start = end + 1;
    current_col++;
  }
  std::cout << "\e[0m" << std::flush;
}

void draw_border(const int obj, const std::pair<int, int>& text_size) {
  // Implementation for drawing border
  if (terminal_manager::obj_border(obj) == 0) return;
  if (terminal_manager::obj_border(obj) != 1) return;

  int top = terminal_manager::obj_x(obj);
  int left = terminal_manager::obj_y(obj);
  int bottom = top + terminal_manager::obj_height(obj);
  int right = left + terminal_manager::obj_width(obj);

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
