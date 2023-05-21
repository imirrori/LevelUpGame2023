#ifndef VISUALIZER_HPP
#define VISUALIZER_HPP

#include "interface/IEntity.hpp"
#include "interface/IVizMenu.hpp"
#include "interface/IVizMap.hpp"
#include "interface/IVizPlayer.hpp"
#include "interface/IVizScore.hpp"
#include "interface/ISettings.hpp"

#include <GLFW/glfw3.h>

#include <KeyManager.hpp>

#include <memory>
#include <vector>
#include <functional>

namespace Visual {
class Visualizer
  : public IMenu
    , public IPlayer
    , public IMap
    , public IScore {
public:

  Visualizer(
    std::shared_ptr<Settings::ISettings>settings,
    std::shared_ptr<KeyManager>         keyManager);
  ~Visualizer();

  // IMenu
  void StartPrint(int count) override;
  void PrintRow(const std::string& name,
                bool               current) override;
  void EndPrint()  override;

  // IPlayer
  void ShowPlayer(Point point) override;

  // IMap
  void PrintBlock(Point point,
                  int   type) override;

  // IScore
  void ShowScore(int score) override;

  bool Show(const std::vector<std::shared_ptr<IEntity> >& dataToShow);

  void KeyCatch(
    int key,
    int scancode,
    int action,
    int mods);

private:

  void func_print_char(const std::string name,
                       const float       where_down,
                       const float       where_right);

  int menu_count_;
  int reverse_menu_count_;

  Point player_point;

  std::shared_ptr<Settings::ISettings>settings_;
  GLFWwindow *window_;
  std::shared_ptr<KeyManager>keyManager_;
};
} // Visual

#endif // VISUALIZER_HPP
