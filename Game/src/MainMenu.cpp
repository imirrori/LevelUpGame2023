#include "MainMenu.hpp"

MainMenu::MainMenu(std::shared_ptr<Visual::IMenu>menuViz)
  : menuViz_(std::move(menuViz))
{}

void MainMenu::onUpdate()
{}

void MainMenu::onRender()
{
  menuViz_->StartPrint(subMenu_.size());

  for (size_t i = 0; i < subMenu_.size(); ++i) {
    menuViz_->PrintRow(subMenu_[i].name_, i == currentMenu_);
  }
  menuViz_->EndPrint();
}

void MainMenu::onCollision()
{}

void MainMenu::AddSubMenu(BaseMenu subMenu)
{
  subMenu_.push_back(std::move(subMenu));
}

void MainMenu::PressKey(KEY key)
{
  switch (key)
  {
    case UP:

      if (currentMenu_ == 0) {
        currentMenu_ = subMenu_.size() - 1;
      } else {
        --currentMenu_;
      }
      break;
    case DOWN:

      if (currentMenu_ == subMenu_.size() - 1) {
        currentMenu_ = 0;
      } else {
        ++currentMenu_;
      }
      break;
    case ENTER:
      subMenu_[currentMenu_].exec_();
  }
}
