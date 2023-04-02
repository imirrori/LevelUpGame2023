#ifndef VISUALIZER_HPP
#define VISUALIZER_HPP

#include "GlobalSettings.hpp"
#include "interface/IPlayer.hpp"
#include "Player.hpp"
#include "interface/IMenu.hpp"
#include "Menu.hpp"

#include <GLFW/glfw3.h>
#include <string>
#include <vector>

namespace Visual {
class Visualizer :
  public IPlayer
  , public IMenu {
public:

  Visualizer(const Settings::GlobalSettings& settings);
  ~Visualizer();

  bool Show(const Player& player,
            const Menu  & menu);
  void ShowPlayer(int x,
                  int y) const override;                 // IPlayer

  void StartPrint(int count) const override;             // IMenu
  void PrintRow(const std::string& name) const override; // IMenu
  void EndPrint() const override;                        // IMenu

private:

  const Settings::GlobalSettings& settings_;
  GLFWwindow *window_;
};
} // Visual

#endif // VISUALIZER_HPP
