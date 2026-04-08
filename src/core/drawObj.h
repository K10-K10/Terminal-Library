#include "core/screen.h"

namespace __terminal__ {
class DrawObj {
 public:
  void put(int y, int x, const Cell& c);
};

extern DrawObj drawObj;
}  // namespace __terminal__
