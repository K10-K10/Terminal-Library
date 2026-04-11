#pragma once

#include <utility>

namespace __terminal__::__input__ {
class Cursor {
 public:
  Cursor() = default;
  ~Cursor() = default;
  enum class MoveDirection { UP, DOWN, LEFT, RIGHT };
  void show();
  void hide();
  void move(int new_row, int new_col);
  void move(std::pair<int, int> new_pos);
  void move(MoveDirection direction);
  void select_object(int obj_id);
  void deselect_object();
  int get_selected_object();
  std::pair<int, int> get_position();

 private:
  struct CursorState {
    int selected_obj_id = -1;
    int row = 0;
    int col = 0;
    bool visible = false;
  };
  CursorState state;
};
}  // namespace __terminal__::__input__

namespace terminal::input {
extern __terminal__::__input__::Cursor cursor;
}
