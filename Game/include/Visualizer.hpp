#ifndef VISUALIZER_HPP
#define VISUALIZER_HPP

#include "interface/IEntity.hpp"
#include "interface/IVizMenu.hpp"
#include "interface/IVizMap.hpp"
#include "interface/IVizPlayer.hpp"
#include "interface/IVizScore.hpp"
#include "interface/ISettings.hpp"

#include "Texture.hpp"

#include <GLFW/glfw3.h>

#include <KeyManager.hpp>

#include <memory>
#include <vector>
#include <functional>
#include <map>

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
  void ShowPlayer(Point          point,
                  PLAYER_STATE_X state_x,
                  PLAYER_STATE_Y state_y) override;
  void ShowCoin(Point coin) override;

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

  struct PlayerVis {
    inline constexpr static int viz_scale = 3;

    Point        player_point;
    unsigned int player_frame_;
  };
  struct CoinVis {
    inline constexpr static int viz_coin_scale = 5;

    Point        coin_point;
    unsigned int coin_frame_;
  };

  void func_print_char(const std::string name,
                       const float       where_down,
                       const float       where_right);
  void LoeadTextures();

  int menu_count_;
  int reverse_menu_count_;
  PlayerVis player_vis_;
  CoinVis coin_vis_;
  std::shared_ptr<Settings::ISettings>settings_;
  GLFWwindow *window_;
  std::shared_ptr<KeyManager>keyManager_;
  std::map<std::string, Textures::Texture>textures_;
};
} // Visual

#endif // VISUALIZER_HPP
