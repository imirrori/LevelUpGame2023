#ifndef VISUALIZER_HPP
#define VISUALIZER_HPP

#include "ISettings.hpp"

#include <GLFW/glfw3.h>
#include <memory>

namespace Visual {
class Visualizer {
public:

  Visualizer(std::shared_ptr<Settings::ISettings>settings);
  ~Visualizer();

  void Mainloop();

private:

  std::shared_ptr<Settings::ISettings>settings_;
  GLFWwindow *window_;
};
} // Visual

#endif // VISUALIZER_HPP
