#include "Visualizer.hpp"

namespace Visual {
Visualizer::Visualizer(std::shared_ptr<Settings::ISettings>settings)
  : settings_(settings)
{
  if (!glfwInit()) {
    throw std::exception{};
  }

  window_ =
    glfwCreateWindow(std::get<int>(settings_->GetValue("visual",
                                                       "window_width")),
                     std::get<int>(        settings_->GetValue("visual",
                                                               "window_height")),
                     std::get<std::string>(settings_->GetValue("visual",
                                                               "window_name")).c_str(),
                     NULL,
                     NULL);

  if (!window_)
  {
    glfwTerminate();
    throw std::exception{};
  }

  glfwMakeContextCurrent(window_);
}

Visualizer::~Visualizer()
{
  glfwTerminate();
}

void Visualizer::Mainloop()
{
  while (!glfwWindowShouldClose(window_))
  {
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT);

    /* Swap front and back buffers */
    glfwSwapBuffers(window_);

    /* Poll for and process events */
    glfwPollEvents();
  }
}
} // Visual
