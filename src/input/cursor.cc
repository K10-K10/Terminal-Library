#include "input/cursor.h"

#include <iostream>
#include <utility>

namespace terminal::input {
void Cursor::show() {
  state.visible = true;
  std::cout << "\x1b[?25h" << std::flush;
}

void Cursor::hide() {
  state.visible = false;
  std::cout << "\x1b[?25l" << std::flush;
}

void Cursor::move(int new_row, int new_col) {
  state.row = new_row;
  state.col = new_col;
  std::cout << "\x1b[" << (new_row + 1) << ";" << (new_col + 1) << "H"
            << std::flush;
}

void Cursor::move(std::pair<int, int> new_pos) {
  move(new_pos.first, new_pos.second);
}

void Cursor::move(MoveDirection direction) {
  switch (direction) {
    case MoveDirection::UP:
      move(state.row - 1, state.col);
      break;
    case MoveDirection::DOWN:
      move(state.row + 1, state.col);
      break;
    case MoveDirection::LEFT:
      move(state.row, state.col - 1);
      break;
    case MoveDirection::RIGHT:
      move(state.row, state.col + 1);
      break;
  }
}

void Cursor::select_object(int obj_id) { state.selected_obj_id = obj_id; }

void Cursor::deselect_object() { state.selected_obj_id = -1; }

int Cursor::get_selected_object() { return state.selected_obj_id; }

std::pair<int, int> Cursor::get_position() { return {state.row, state.col}; }

terminal::input::Cursor::CursorState terminal::input::Cursor::state{};

}  // namespace terminal::input
