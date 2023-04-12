#ifndef GLOBALSETTINGS_H
#define GLOBALSETTINGS_H

#include <string>

namespace Settings {
class GlobalSettings {
public:

  static constexpr int window_width  = 640;
  static constexpr int window_height = 480;

  static constexpr int field_width  = 50;   // согласовать с Дмитрием
  static constexpr int field_height = 25;   // согласовать с Дмитрием
  static constexpr int map_lenght   = 1249; // согласовать с Дмитрием длинну
                                            // карты

  const char *window_name = "Mario";

  static constexpr int player_size   = 1;
  static constexpr int menu_str_size = 3;
};
} // Settings

#endif // GLOBALSETTINGS_H
