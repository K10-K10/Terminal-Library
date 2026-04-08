#include "obj/text.h"

#include <string>

#include "core/drawObj.h"
#include "layout/rect.h"

namespace terminal {
Text& Text::set_text(const std::string& text) {
  text_ = text;
  return *this;
}

std::string Text::get_text() { return text_; }

Text& Text::push(char c) {
  text_.push_back(c);
  return *this;
}

Text& Text::pop() {
  if (!text_.empty()) text_.pop_back();
  return *this;
}

void Text::draw(const Rect& r) {
  // Implementation for drawing text
  int cnt_x = 0;
  int cnt_y = 0;
  for (char c : text_) {
    if (c == '\n') {
      if (r.w - cnt_x > 0) {
        for (int j = r.x + cnt_x; j <= r.w; ++j) {
          __terminal__::drawObj.put(r.y + cnt_y, r.x + cnt_x, {' '});
        }
      } else {
        cnt_x = 0;
        ++cnt_y;
      }
    } else {
      __terminal__::drawObj.put(r.x + cnt_x, r.y + cnt_y, {c});
      ++cnt_x;
      if (cnt_x >= r.w) {
        cnt_x = 0;
        ++cnt_y;
      }
    }
  }
  return;
}

}  // namespace terminal
