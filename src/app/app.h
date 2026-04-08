#include <csignal>
#include <functional>

#include "core/render.h"
#include "core/screen.h"

namespace __terminal__ {
class App {
 public:
  void init(int fps = 60);
  void loop(std::function<void()> frame);
  void pose();
  void stop();

 protected:
  bool runnning = false;
  bool pose = false;
  static std::sig_atomic_t sig_num;

 private:
  Render& render;
  int width = 0, height = 0;
  int fps;
  static void signal_handler(int sig);
};
}  // namespace __terminal__
