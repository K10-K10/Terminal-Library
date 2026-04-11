#include "obj/list.h"

#include <string>
#include <vector>

#include "core/drawObj.h"
#include "layout/rect.h"

namespace terminal {
List& List::set_pos(const Rect& r) {
  rect = r;
  return *this;
}

List& List::set_items(std::vector<std::string> items) {
  items_ = std::move(items);
  selected_ = 0;
  return *this;
}

const std::vector<std::string>& List::items() const { return items_; }

List& List::add_item(const std::string& s) {
  items_.push_back(s);
  return *this;
}

const std::string List::selected_item() const {
  if (items_.empty())
    return "";
  else
    return items_[selected_];
}

void List::move_up() {
  if (selected_ > 0) {
    --selected_;
  }

  if (selected_ < draw_index_num_) {
    draw_index_num_ = selected_;
  }
}

void List::move_down() {
  int max_items = static_cast<int>(items_.size());
  if (selected_ + 1 < max_items) {
    ++selected_;
  }

  int view_height = rect.h;

  if (selected_ >= draw_index_num_ + view_height) {
    draw_index_num_ = selected_ - view_height + 1;
  }
}

int List::selected_index() const { return selected_; }
void List::draw() {
  int x = rect.x;
  int y = rect.y;
  int w = rect.w;
  int h = rect.h;

  int max_items = items_.size();

  for (int i = 0; i < h; ++i) {
    int idx = draw_index_num_ + i;

    int cy = y + i;

    for (int j = 0; j < w; ++j) {
      __terminal__::drawObj.put(cy, x + j, {" "});
    }

    if (idx >= max_items) continue;

    const std::string& text = items_[idx];
    bool selected = (idx == selected_);

    __terminal__::drawObj.put(cy, x, {selected ? ">" : " "});

    int max_width = w - 1;

    for (int j = 0; j < max_width && j < (int)text.size(); ++j) {
      __terminal__::drawObj.put(cy, x + 1 + j, {std::string(1, text[j])});
    }
  }
}

}  // namespace terminal
