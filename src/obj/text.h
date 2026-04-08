#include <string>

#include "obj/obj.h"

namespace terminal {

class Text : private Object {
 public:
  Text& set_text(const std::string& text);
  std::string get_text();
  Text& push(char c);
  Text& pop();
  void draw(const Rect& r) override;

 private:
  std::string text_;
};

}  // namespace terminal
