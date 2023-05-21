#ifndef IVIZMAP_HPP
#define IVIZMAP_HPP

#include "Point.h"

#include <cstdlib>

namespace Visual {
class IMap {
public:

  virtual ~IMap() = default;
  virtual void PrintBlock(Point point,
                          int   type) = 0;
};
} // Visual

#endif // IVIZMAP_HPP
