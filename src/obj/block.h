#pragma once

#include "obj/obj.h"

namespace terminal {
class Rect;

class Block : public Object {
 public:
  void draw() override;
  Block& set_pos(const Rect& r);
  Block& set_type(int new_type);
  int get_type();

 private:
  int type_;
  Rect rect;
  struct Border {
    const char* tl;  // top-left
    const char* tr;
    const char* bl;
    const char* br;

    const char* h;  // horizontal
    const char* v;  // vertical
  };

  const Border single{"┌", "┐", "└", "┘", "─", "│"};

  const Border bold{"┏", "┓", "┗", "┛", "━", "┃"};

  const Border double_line{"╔", "╗", "╚", "╝", "═", "║"};
};

}  // namespace terminal
