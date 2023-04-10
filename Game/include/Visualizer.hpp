#ifndef VISUALIZER_HPP
#define VISUALIZER_HPP

#include "GlobalSettings.hpp"
#include "interface/IPlayer.hpp"
#include "Player.hpp"
#include "interface/IMenu.hpp"
#include "Menu.hpp"
#include "interface/IMap.hpp"

#include <GLFW/glfw3.h>
#include <string>
#include <vector>

namespace Visual {
class Visualizer :
  public IPlayer
  , public IMenu
  , public IMap {
public:

  Visualizer(const Settings::GlobalSettings& settings);
  ~Visualizer();

  bool               Show(const Player& player);
  void               ShowPlayer(int x,
                                int y) const override;           // IPlayer

  void               StartPrint(int count) override;             // IMenu
  void               PrintRow(const std::string& name) override; // IMenu
  void               EndPrint()  override;                       // IMenu

  std::size_t        width() const override;                     // IMap
  std::size_t        height() const override;                    // IMap
  const std::string& GetMap() const override;                    // IMap
  void               PrintMap(const std::string& map);

private:

  const Settings::GlobalSettings& settings_;
  int menu_count_;
  GLFWwindow *window_;
};
} // Visual

#endif // VISUALIZER_HPP
