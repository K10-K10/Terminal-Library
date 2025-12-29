# object

## constructor

```c++
terminal::Object object_name(title, contents, x, y, hight, width, border_type);
```

### border_type
`0` - None
`1` - singe
> `2` - double
> `3` - curved

## operator =

Change contents.

```c++
obj = "test";
```

## operator ()

Return title or contents

0 - Return title
1 - Return contents

## operator [] 

Return settings.

0 - Whether the object is displayed (0/1)
1 - Object x
2 - Object y
3 - Object width
4 - Object height
5 - Contents width
6 - Contents height
7 - Contents text colour
8 - COntents fill colour
9 - Border type
