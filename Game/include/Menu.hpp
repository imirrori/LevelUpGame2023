#ifndef MENU_HPP
#define MENU_HPP

#include "interface/IMenu.hpp"
#include <memory>
#include <vector>

class Menu {
public:

  Menu(std::shared_ptr<IMenu>viz, const std::vector<std::string>& names)
    : viz_(std::move(viz))
    , names_row_(std::move(names))
  {
    // names_row_.emplace_back(name);
  }

  void show() const
  {
    viz_->PrintRow(names_row_);
  }

private:

  std::shared_ptr<IMenu>viz_;
  std::vector<std::string>names_row_;
};

#endif // MENU_HPP
