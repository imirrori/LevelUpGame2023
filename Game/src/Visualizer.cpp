#include "Visualizer.hpp"
#include <stdlib.h>
#include <stdio.h>

#include "Global_settings.h"

///////////////////////////////////////
// для проверки
class Player {
public:

  int x;
  int y;
};

///////////////////////////////////////

namespace Visual {
void Visualizer::make_window()
{
  ///////////////////////////////////////
  // для проверки
  Player player = { 1, 1 };
  GlobalSettings setting;

  //////////////////////////////////////

  // отобрать отдельно Init и отрисоку всего остального
  GLFWwindow *window;

  if (!glfwInit()) exit(EXIT_FAILURE);

  window = glfwCreateWindow(setting.window_width,
                            setting.window_height,
                            setting.window_name,
                            NULL,
                            NULL);

  if (!window)
  {
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwMakeContextCurrent(window);

  while (!glfwWindowShouldClose(window))
  {
    int width;
    int height;

    glfwGetFramebufferSize(window, &width, &height);

    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // размер поля в бобрах- слева, справа, низ, верх, близко, далеко
    glOrtho(0, setting.field_width, 0, setting.field_height, 0, 10);

    ///////////////////////////////////////
    // для проверки
    glBegin(GL_POLYGON);                        // начало отрисовки полигона
                                                // персонажа

    glColor3f(1, 0.0, 0.0);                     // RGB
    glVertex2d(player.x * setting.player_size,
               player.y * setting.player_size); // вправо(x), вверх(y)
    glVertex2d(player.x * setting.player_size + setting.player_size,
               player.y * setting.player_size);
    glVertex2d(player.x * setting.player_size + setting.player_size,
               player.y * setting.player_size + setting.player_size);
    glVertex2d(player.x * setting.player_size,
               player.y * setting.player_size + setting.player_size);

    glEnd(); // конец отрисовки полигона персонажа
    ///////////////////////////////////////


    glfwSwapBuffers(window); // обмен буферов
    glfwPollEvents();        // обработчик событий, проверяет не зависло ли окно
  }
  glfwDestroyWindow(window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}
}
