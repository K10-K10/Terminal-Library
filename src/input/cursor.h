#pragma once

#ifndef TERMINAL_LIBRARY_INPUT_CURSOR_H_
#define TERMINAL_LIBRARY_INPUT_CURSOR_H_

#include <utility>
namespace terminal::input {
class Cursor {
 public:
  Cursor() = default;
  ~Cursor() = default;
  enum class MoveDirection { UP, DOWN, LEFT, RIGHT };
  static void show();
  static void hide();
  static void move(int new_row, int new_col);
  static void move(std::pair<int, int> new_pos);
  static void move(MoveDirection direction);
  static void select_object(int obj_id);
  static void deselect_object();
  static int get_selected_object();
  static std::pair<int, int> get_position();

 private:
  struct CursorState {
    int selected_obj_id = -1;
    int row = 0;
    int col = 0;
    bool visible = false;
  };
  static CursorState state;
};
}  // namespace terminal::input

#endif  // TERMINAL_LIBRARY_INPUT_CURSOR_H_
