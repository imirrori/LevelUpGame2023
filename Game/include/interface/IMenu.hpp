#ifndef IMENU_HPP
#define IMENU_HPP

#include <string>

class IMenu {
public:

  virtual ~IMenu() = default;

  virtual void StartPrint(int count) const             = 0;
  virtual void PrintRow(const std::string& name) const = 0;
  virtual void EndPrint() const                        = 0;
};

// проверка для коммита
#endif // IMENU_HPP
