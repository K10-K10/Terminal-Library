#pragma once

#ifndef TERMINAL_COLOR
#define TERMINAL_COLOR

namespace terminal {
// text
#define text_black 30
#define text_red 31
#define text_green 32
#define text_yellow 33
#define text_blue 34
#define text_magenta 35
#define text_sian 36
#define text_gray 37
// fill
#define fill_black 40
#define fill_red 41
#define fill_green 42
#define fill_yellow 43
#define fill_blue 44
#define fill_magenta 45
#define fill_sian 46
#define fill_gray 47

int print_color(const int &txt_color, const char *str);
int print_color(const int &txt_color, const int &fill_color, const char *str);

} // namespace terminal

#endif
