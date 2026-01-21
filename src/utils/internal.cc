#include "utils/internal.h"

#include "utils/base.h"

namespace terminal::internal {

static ScreenSize screen_size{0, 0};

void update_screen_size() {
  screen_size.rows = utils::GetTerminalRows();
  screen_size.cols = utils::GetTerminalColumns();
}

ScreenSize get_screen_size() { return screen_size; }

}  // namespace terminal::internal
