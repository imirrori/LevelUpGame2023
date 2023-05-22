#ifndef _MAINMENU_HPP_
#define _MAINMENU_HPP_

#include "interface/IEntity.hpp"
#include "interface/IVizMenu.hpp"

#include <vector>
#include <functional>
#include <string>
#include <memory>


class MainMenu
  : public IEntity {
public:

  enum KEY
  {
    UP,
    DOWN,
    ENTER
  };

  struct BaseMenu {
    std::string          name_;
    std::function<bool()>exec_;
  };

  MainMenu(std::shared_ptr<Visual::IMenu>menuViz);
  virtual ~MainMenu() = default;

  void onUpdate(std::chrono::nanoseconds duration) override;

  void onRender() override;
  void onCollision() override;

  void AddSubMenu(BaseMenu subMenu);
  bool PressKey(KEY key);

private:

  std::shared_ptr<Visual::IMenu>menuViz_;
  std::vector<BaseMenu>subMenu_;
  size_t currentMenu_ = 0;
};

#endif // _MAINMENU_HPP_
