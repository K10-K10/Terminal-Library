#pragma once

#ifndef TERMINAL_LIBRARY_INPUT_KEYBOARD_H_
#define TERMINAL_LIBRARY_INPUT_KEYBOARD_H_

namespace terminal::input {
enum class KeyCode {
  NONE,
  UNKNOWN,
  ESC,
  ENTER,
  BACKSPACE,
  TAB,
  ESCAPE,
  UP,
  DOWN,
  LEFT,
  RIGHT,
  SPACE,
  CHAR,
  // Add other key codes as needed
};

class Key {
 public:
  Key();
  ~Key();
  void init();
  void show();
  void hide();

  KeyCode getKeyCode() const;
  char getCurrentChar() const;
  bool read();

 private:
  KeyCode key_code = KeyCode::NONE;
  char current_char = 0;
  bool is_visible = false;

  enum class KeyState { PRESSED, RELEASED } key_state;
  enum class Modifier { NONE = 0, SHIFT = 1, CTRL = 2, ALT = 4 } modifier;
};

}  // namespace terminal::input
#endif  // TERMINAL_LIBRARY_INPUT_KEYBOARD_H_
