#ifndef GLOBALSETTINGS_H
#define GLOBALSETTINGS_H

#include <string>

namespace Settings {
class GlobalSettings {
public:

  static constexpr int window_width  = 640;
  static constexpr int window_height = 480;

  static constexpr int field_width  = 50;
  static constexpr int field_height = 25;

  const char *window_name = "Mario";

  static constexpr int player_size = 1;
};
} // Settings

#endif // GLOBALSETTINGS_H
