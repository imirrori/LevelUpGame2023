#include "MainMenu.hpp"

MainMenu::MainMenu(std::shared_ptr<IMenu>menuViz)
  : menuViz_(std::move(menuViz))
{}

void MainMenu::onUpdate()
{}

void MainMenu::onRender()
{
  menuViz_->StartPrint(subMenu_.size());

  for (const auto& subMenu: subMenu_) {
    menuViz_->PrintRow(subMenu.name_);
  }
  menuViz_->EndPrint();
}

void MainMenu::onCollision()
{}

void MainMenu::AddSubMenu(BaseMenu subMenu)
{
  subMenu_.push_back(std::move(subMenu));
}
