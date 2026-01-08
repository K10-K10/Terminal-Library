#include "input/keyboard.h"

#include <ncurses.h>

#include <iostream>
#include <string>

#include "utils/base.h"

namespace terminal::input {
Key::Key() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
  is_visible = false;
}

void Key::init() {}

void Key::show() {
  is_visible = true;
  // Implementation for showing the key (if applicable)
}

void Key::hide() {
  is_visible = false;
  // Implementation for hiding the key (if applicable)
}

KeyCode Key::getKeyCode() const { return key_code; }
char Key::getCurrentChar() const { return current_char; }

bool Key::read() {
  int ch = getch();
  if (ch == ERR) return false;

  key_code = KeyCode::UNKNOWN;
  current_char = 0;

  switch (ch) {
    case KEY_UP:
      key_code = KeyCode::UP;
      break;
    case KEY_DOWN:
      key_code = KeyCode::DOWN;
      break;
    case KEY_LEFT:
      key_code = KeyCode::LEFT;
      break;
    case KEY_RIGHT:
      key_code = KeyCode::RIGHT;
      break;

    case 27:
      key_code = KeyCode::ESC;
      break;
    case '\n':
      key_code = KeyCode::ENTER;
      break;
    case '\t':
      key_code = KeyCode::TAB;
      break;
    case KEY_BACKSPACE:
    case 127:
      key_code = KeyCode::BACKSPACE;
      break;

    case ' ':
      key_code = KeyCode::SPACE;
      current_char = ' ';
      break;

    default:
      if (ch >= 0 && ch <= 255) {
        key_code = KeyCode::CHAR;
        current_char = static_cast<char>(ch);
      }
      break;
  }

  if (is_visible) terminal::utils::BackSpace();
  return true;
}

Key::~Key() { endwin(); };
}  // namespace terminal::input
