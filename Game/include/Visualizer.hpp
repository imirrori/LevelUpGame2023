#ifndef VISUALIZER_HPP
#define VISUALIZER_HPP

#include "GlobalSettings.hpp"

#include <GLFW/glfw3.h>

namespace Visual {
class Visualizer {
public:

  Visualizer(const Settings::GlobalSettings& settings);
  ~Visualizer();

  void Mainloop();

private:

  const Settings::GlobalSettings& settings_;
  GLFWwindow *window_;
};
} // Visual

#endif // VISUALIZER_HPP
