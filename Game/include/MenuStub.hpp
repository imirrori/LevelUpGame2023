#ifndef MENUSTUB_HPP
#define MENUSTUB_HPP

#include "IEntity.hpp"
#include "IMenu.hpp"

#include <memory>

class MenuStub
  : public IEntity {
public:

  MenuStub(std::shared_ptr<IMenu>menuViz)
    : menuViz_(std::move(menuViz))
  {}

  void onUpdate() override {}

  void onRender() override    {
    menuViz_->StartPrint(3);
    menuViz_->PrintRow("start game");
    menuViz_->PrintRow("load game");
    menuViz_->PrintRow("end game");
    menuViz_->EndPrint();
  }

  void onCollision() override {}

private:

  std::shared_ptr<IMenu>menuViz_;
};


#endif // MENUSTUB_HPP
