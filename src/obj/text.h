#pragma once

#include <string>

#include "obj/obj.h"

namespace terminal {

class Text : private Object {
 public:
  Text& set_pos(const Rect& r);
  Text& set_text(const std::string& text);
  std::string get_text();
  Text& push(char c);
  Text& pop();
  void draw() override;

 private:
  Rect rect;
  std::string text_;
};

}  // namespace terminal
