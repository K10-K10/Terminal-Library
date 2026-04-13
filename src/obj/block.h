#pragma once

#include "layout/border.h"
#include "layout/rect.h"
#include "obj/obj.h"

namespace terminal {
class Block : public Object {
 private:
 public:
  void draw() override;
  Block& position(const Rect& r);
  Block& border_type(const BorderType::Border& type);
  Block& borders(const Borders::EdgeType type_);

 private:
  Rect rect;
  const BorderType::Border* style_ = &BorderType::SINGLE;
  Borders::EdgeType edges_ = Borders::ALL;
};

}  // namespace terminal
