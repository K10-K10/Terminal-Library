# App

`app` is the main class of the library. It is responsible for managing the application state, rendering the UI, and handling user input.

## API List


### 1. `app.init()`

- Arguments: None
- Return Value: None

Initializes the application. This function must be called before any other functions are used.
When this function is called, the terminal enter the alternate screen and hide the cursor.

### 2. `app.loop(funcs)`

- Arguments: `std::function<void()> funcs` (a list of functions to be called in each loop iteration)
- Return Value: None

Starts the main loop of the application. The provided functions will be called in each iteration of the loop, allowing you to update the UI and handle user input.

### 3. `app.stop()`
- Arguments: None
- Return Value: None

Stops the main loop and exits from alternate screen.
You should call this function when you want to exit the application.

author: K10-K10
update: 12/04/2026
