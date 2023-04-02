#ifndef MENU_HPP
#define MENU_HPP

#include "interface/IMenu.hpp"
#include <memory>

class Menu {
public:

  Menu(std::shared_ptr<IMenu>viz, const std::string& name)
    : viz_(std::move(viz))
    , name_row_(name)
  {}

  void show() const
  {
    viz_->PrintRow(name_row_);
  }

  //  virtual void StartPrint(int count);
  //  virtual void PrintRow(const std::string& name);
  //  virtual void EndPrint();

private:

  std::shared_ptr<IMenu>viz_;
  std::string name_row_;
};

#endif // MENU_HPP
