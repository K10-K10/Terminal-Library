#pragma once

#include <string>
#include <vector>

#include "layout/rect.h"
#include "obj/obj.h"

namespace terminal {

class List : public Object {
 public:
  List& set_pos(const Rect& r);
  List& set_items(std::vector<std::string> items);
  const std::vector<std::string>& items() const;
  List& add_item(const std::string& s);
  const std::string selected_item() const;
  // TODO: heightlite selected item
  // TODO: scroll, set symbol
  void move_up();
  void move_down();
  int selected_index() const;
  void draw() override;

 private:
  Rect rect;
  std::vector<std::string> items_;
  std::string selector_symbol;
  int selected_ = 0;
  int draw_index_num_ = 0;
};

}  // namespace terminal
