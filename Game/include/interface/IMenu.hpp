#ifndef IMENU_HPP
#define IMENU_HPP

#include <string>
#include <vector>

class IMenu {
public:

  virtual ~IMenu() = default;

  virtual void StartPrint(int count) const                           = 0;
  virtual void PrintRow(const std::vector<std::string>& names) const = 0;
  virtual void EndPrint() const                                      = 0;
};

#endif // IMENU_HPP
