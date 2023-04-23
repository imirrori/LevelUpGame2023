#ifndef _MAINMENU_HPP_
#define _MAINMENU_HPP_

#include "interface/IEntity.hpp"
#include "interface/IMenu.hpp"

#include <vector>
#include <functional>
#include <string>
#include <memory>


class MainMenu
  : public IEntity {
public:

  struct BaseMenu {
    std::string          name_;
    std::function<void()>exec_;
  };

  MainMenu(std::shared_ptr<IMenu>menuViz);
  virtual ~MainMenu() = default;

  void onUpdate() override;

  void onRender() override;
  void onCollision() override;

  void AddSubMenu(BaseMenu subMenu);

private:

  std::shared_ptr<IMenu>menuViz_;
  std::vector<BaseMenu>subMenu_;
};

#endif // _MAINMENU_HPP_
