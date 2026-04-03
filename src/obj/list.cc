#include "obj/list.h"

#include <string>
#include <vector>

namespace terminal {
List& List::set_items(std::vector<std::string> items) {
  items_ = std::move(items);
  items_ = items;
  selected_ = 0;
  return *this;
}

const std::vector<std::string>& List::items() const { return items_; }

List& List::add_item(const std::string& s) {
  items_.push_back(s);
  return *this;
}

const std::string& List::selected_item() const {
  if (items_.empty())
    return "";
  else
    return items_[selected_];
}

void List::move_up() {
  if (selected_ > 0) --selected_;
}

void List::move_down() {
  if (selected_ < items_.size()) ++selected_;
}

int List::selected_index() const { return selected_; }

void draw(Screen& s, const Rect& r) {}

}  // namespace terminal
