#ifndef IVIZMENU_H
#define IVIZMENU_H

#include <string>

namespace Visual {
class IMenu {
public:

  virtual ~IMenu() = default;

  virtual void StartPrint(int count) = 0;
  virtual void PrintRow(const std::string& name,
                        bool               current) = 0;
  virtual void EndPrint()                           = 0;
};
}

#endif // IVIZMENU_H
