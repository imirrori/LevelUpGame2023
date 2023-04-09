#include "GlobalSettings.hpp"

#include "Visualizer.hpp"

#include <stdlib.h>
#include <stdio.h>

namespace Visual {
Visualizer::Visualizer(const Settings::GlobalSettings& settings)
  : settings_(settings)
{
  if (!glfwInit()) {
    throw std::exception{};
  }

  window_ = glfwCreateWindow(settings_.window_width,
                             settings_.window_height,
                             settings_.window_name,
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
