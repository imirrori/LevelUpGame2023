#ifndef GLOBAL_SETTINGS_H
#define GLOBAL_SETTINGS_H

#include <string>

class GlobalSettings {
public:

  static constexpr  int window_width  = 640;
  static constexpr  int window_height = 480;

  static constexpr  int field_width  = 50;
  static constexpr  int field_height = 25;

  const char *window_name          = "Mario";
  static constexpr int player_size = 1;
};

#endif // GLOBAL_SETTINGS_H
