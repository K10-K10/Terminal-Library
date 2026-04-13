# Points to Note

Here are some important points to note when using the TUI library:

1. **Coordinate System**: The TUI library uses a coordinate system where the top-left corner of the terminal is (0, 0). The x-coordinate increases to the right, and the y-coordinate increases downwards.

2. **Where to Draw**: When `app` is initialized, it entered alternate window, and when `app.stop()` called, it will exit alternate window.

3. **If process stopped by `Ctrl + C`**: This library has a signal handler for `SIGINT`, and when the process is stopped by `Ctrl + C`, auto call `app.stop()`, so the terminal will be restored to its original state.

author: K10-K10
update: 12/04/2026
