#pragma once

namespace BorderType {
struct Border {
  const char* tl;  // top-left
  const char* tr;
  const char* bl;
  const char* br;
  const char* h;  // horizontal
  const char* v;  // vertical
};

inline const Border SINGLE{"┌", "┐", "└", "┘", "─", "│"};
inline const Border ROUNDED{"╭", "╮", "╰", "╯", "─", "│"};
inline const Border BOLD{"┏", "┓", "┗", "┛", "━", "┃"};
inline const Border DOUBLE{"╔", "╗", "╚", "╝", "═", "║"};
}  // namespace BorderType

namespace Borders {
using EdgeType = int;

constexpr EdgeType NONE = 0;
constexpr EdgeType TOP = 1 << 0;
constexpr EdgeType BOTTOM = 1 << 1;
constexpr EdgeType LEFT = 1 << 2;
constexpr EdgeType RIGHT = 1 << 3;
constexpr EdgeType ALL = TOP | BOTTOM | LEFT | RIGHT;
}  // namespace Borders
