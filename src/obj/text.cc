#include "obj/text.h"

#include <string>

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

void Text::draw(Screen& s, const Rect& r) {
  // Implementation for drawing text
}
}  // namespace terminal
