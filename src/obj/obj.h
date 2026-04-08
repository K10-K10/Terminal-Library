namespace terminal {

struct Rect;
class Screen;

class Object {
 public:
  virtual void draw(const Rect&) = 0;
  virtual ~Object() = default;
};

}  // namespace terminal
