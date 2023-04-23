#ifndef IMENU_HPP
#define IMENU_HPP

#include <string>

class IMenu {
public:

  virtual ~IMenu() = default;

  virtual void StartPrint(int count)             = 0;
  virtual void PrintRow(const std::string& name) = 0;
  virtual void EndPrint()                        = 0;
};

#endif // IMENU_HPP
