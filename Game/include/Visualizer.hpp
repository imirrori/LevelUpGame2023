#ifndef VISUALIZER_HPP
#define VISUALIZER_HPP

#include "interface/IEntity.hpp"
#include "interface/IMap.hpp"
#include "interface/IMenu.hpp"
#include "interface/IPlayer.hpp"
#include "interface/ISettings.hpp"

#include <GLFW/glfw3.h>

#include <memory>
#include <vector>

namespace Visual {
class Visualizer
  : public IMenu
    , public IPlayer
    , public IMap {
public:

  Visualizer(std::shared_ptr<Settings::ISettings>settings);
  ~Visualizer();

  // IMenu
  void         StartPrint(int count) override;
  void         PrintRow(const std::string& name) override;
  void         EndPrint()  override;

  // IPlayer
  virtual void ShowPlayer(int x,
                          int y) override;

  // IMap
  std::size_t        width()  const override;
  std::size_t        height() const override;
  const std::string& GetMap()const  override;
  void               PrintMap(const std::string& map,
                              const std::size_t& width,
                              const std::size_t& height) override;

  // Visualizer's method
  bool Show(
    const std::vector<std::shared_ptr<IEntity> >& dataToShow,
    const std::shared_ptr<IMap>                 & map);

private:

  // Visualizer's method
  void func_print_char(const std::string name,
                       const float       where_down,
                       const float       where_right);

  // Visualizer's fields
  int menu_count_;
  int reverse_menu_count_;
  std::shared_ptr<Settings::ISettings>settings_;
  GLFWwindow *window_;
};
} // Visual

#endif // VISUALIZER_HPP
