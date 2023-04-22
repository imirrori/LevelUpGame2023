#ifndef VISUALIZER_HPP
#define VISUALIZER_HPP

#include "IEntity.hpp"
#include "IMenu.hpp"
#include "IPlayer.hpp"
#include "ISettings.hpp"

#include <GLFW/glfw3.h>

#include <memory>
#include <vector>

namespace Visual {
class Visualizer
  : public IMenu
  , public IPlayer {
public:
  //Visualizer(const Settings::GlobalSettings& settings);
  Visualizer(std::shared_ptr<Settings::ISettings>settings);
  ~Visualizer();
  GLFWwindow *GetWindowInstance() const { return window_; }

  // IMenu
  void         StartPrint(int count)             override;
  void         PrintRow(const std::string& name) override;
  void         EndPrint()                        override;

  // IPlayer
  void ShowPlayer(const int& x, const int& y)    override;
  void OnInit()                                  override;
  void OnUpdate(double deltaTime = 0.0)          override;
  void OnRender()                                override;

  bool Show(const std::vector<std::shared_ptr<IEntity> >& dataToShow);

private:
  //const Settings::GlobalSettings& settings_;

  void func_print_char(const std::string name,
                       const float       where_down,
                       const float       where_right);

  int menu_count_;
  int reverse_menu_count_;

  std::shared_ptr<Settings::ISettings>settings_;
  GLFWwindow *window_;
};
} // Visual

#endif // VISUALIZER_HPP
