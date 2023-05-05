#ifndef IVIZMAP_HPP
#define IVIZMAP_HPP

#include <cstdlib>

namespace Visual {
class IMap {
public:

  virtual ~IMap() = default;
  virtual void PrintBlock(size_t x,
                          size_t y,
                          int    type) = 0;
};
} // Visual

#endif // IVIZMAP_HPP
