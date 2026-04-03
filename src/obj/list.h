#pragma once
#include <string>
#include <vector>

#include "obj/obj.h"

namespace terminal {

class List : public Object {
 public:
  List& set_items(std::vector<std::string> items);
  const std::vector<std::string>& items() const;
  List& add_item(const std::string& s);
  const std::string& selected_item() const;
  void move_up();
  void move_down();
  int selected_index() const;
  void draw(Screen& s, const Rect& r) override;

 private:
  std::vector<std::string> items_;
  int selected_ = 0;
};

}  // namespace terminal
