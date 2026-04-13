# Text

`Text` is an object that can render a string of text.It supports various styles, automatic wrapping, and alignment.

## API List

### 1. `Text` constructor

- Arguments: None
- Return Value: None

Creates a new `Text` object.

### 2. `text.set_pos(rect)`
- Arguments: `rect` (a `Rect` object that defines the position and size of the text)
- Return Value: None

Sets the position and size of the text.

### 3. `text.set_text(content)`
- Arguments: `content` (a string containing the text to display)
- Return Value: None

Sets the text content of the `Text` object.

### 4. `text.get_text()`
- Arguments: None
- Return Value: A string containing the current text content of the `Text` object.

Returns the current text content of the `Text` object.

### 5. `text.push(c)`
- Arguments: `c` (a character to append to the text)
- Return Value: None

Appends a character to the end of the current text content.

### 6. `text.pop()`
- Arguments: None
- Return Value: None

Removes the last character from the current text content.

### 7. `text.draw()`
- Arguments: None
- Return Value: None

Draws the text on the terminal at the specified position and with the specified styles.

author: K10-K10
update: 12/04/2026
