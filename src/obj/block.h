#include "obj/obj.h"

namespace terminal {
class Block : public Object {
 public:
  void draw(Screen& s, const Rect& r) override;
  Block& set_type(int new_type);
  int get_type();

 private:
  int type_;
};

}  // namespace terminal
