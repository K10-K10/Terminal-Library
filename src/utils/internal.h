namespace terminal::internal {

struct ScreenSize {
  int rows;
  int cols;
};

void update_screen_size();
ScreenSize get_screen_size();

}  // namespace terminal::internal
