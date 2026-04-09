#include "core/drawObj.h"

#include "core/screen.h"

namespace __terminal__ {
void DrawObj::put(int y, int x, const Cell& c) {
  terminal::screen.put(y, x, c);
  return;
}

DrawObj drawObj;

}  // namespace __terminal__
