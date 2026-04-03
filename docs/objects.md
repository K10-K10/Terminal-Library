# Object Documentation

This document provides information about the terminal objects available in the Terminal Library and how to manipulate them.

## What is a Terminal Object?
A terminal object represents a visual element that can be rendered in the terminal. Examples of terminal objects include boxes, text labels, buttons, and other UI components.

## initializing Objects
If you want to render an object, you need to start `Terminal`.[see Terminal Documentation](terminal.md)

```cpp
terminal::Object obj(const std::string& title,
                     const std::string& content,
                     int row,
                     int col,
                     int height = 0,
                     int width = 0,
                     int border_style = 0
                     );
```

- `title`: The title of the object.
- `content`: The content displayed within the object.
- `row`: The row position of the object in the terminal.
- `col`: The column position of the object in the terminal.
- `height`: The height of the object. If set to 0, it will auto adjust based on content.
- `width`: The width of the object. If set to 0, it will auto adjust based on content.
- `border_style`: The style of the border around the object.
  - 0: No border
  - 1: Single line border

## Operators

- `operator=`: Assign content from `std::string` to the object.
- `operator+=`: Append content from `std::string` to the object.
- `operator[](int)`: Get object info
  - `0`: show/hide status
  - `1`: row position
  - `2`: column position
  - `3`: height
  - `4`: width
  - `5`: text_width
  - `6`: text_height
  - `7`: text_colour
  - `8`: fill_colour
  - `9`: border_style
- `operator()(int)`: Get Object contents
  - `0`: title
  - `1`: content
  
## Functions
- `clear()`: Clear the content of the object.
- `show()`: Render the object in the terminal.
- `hide()`: Remove the object from the terminal.
- `title(const std::string& new_title)`: Set a new title for the object.
- `text(const std::string& new_text)`: Set new content for the object.
- `move(int new_row, int new_col)`: Move the object to a new position
- `resize(int new_height, int new_width, int border_style)`: Resize the object

- `changeTextColor(int new_text_color)`: Change the text color of the object.
- `changeFillColor(int new_fill_color)`: Change the fill color of the object.
