#include "Visualizer.hpp"

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

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

bool Visualizer::Show(const Player& player, const Menu& menu) //  передать
                                                              // вектор объектов
                                                              // Entity
{
  if (glfwWindowShouldClose(window_))
  {
    return false;
  }

  do
  {
    glLoadIdentity();             // считывает текущую матрицу
    glClear(GL_COLOR_BUFFER_BIT); // очистка буфера
    glOrtho(0, settings_.field_width, 0, settings_.field_height, 0, 10);

    //    menu.show(); // отрисовка меню

    std::string my_map =
      "#################################################"
      "#################################################"
      "#################################################"
      "#################################################"
      "######################s##########################"
      "######################s##########################"
      "#################################################"
      "#################################################"
      "#################################################"
      "#################################################"
      "#################################################"
      "#################################################"
      "#################################################"
      "ccccccc##########################################"
      "#################################################"
      "#################################################"
      "###########################sssss#################"
      "#################################################"
      "#################################################"
      "############mmmm#################################"
      "#################################################"
      "############mmmm#################################"
      "#################################################"
      "#################################################"
      "#################################################";

    PrintMap(my_map);         // карта
    player.show();            // отрисовка персонажа

    glfwSwapBuffers(window_); // обмен буферов
    glfwPollEvents();         // обработчик событий, проверяет не зависло ли
                              // окно
  }

  while (!glfwWindowShouldClose(window_));

  return true;
}

void Visualizer::ShowPlayer(int x, int y) const // override by IPlayer
{
  // почему ShowPlayer не знает о глобальных настройках внутри Visualizer?
  // начало отрисовки полигона персонажа
  glBegin(GL_POLYGON);

  glColor3f(1, 1, 1);                                    // RGB
  glVertex2d(x * Settings::GlobalSettings::player_size,
             y * Settings::GlobalSettings::player_size); // вправо(x), вверх(y)
  glVertex2d(
    y  * Settings::GlobalSettings::player_size + Settings::GlobalSettings::player_size,
    x  * Settings::GlobalSettings::player_size);
  glVertex2d(
    y  * Settings::GlobalSettings::player_size + Settings::GlobalSettings::player_size,
    x  * Settings::GlobalSettings::player_size +
    Settings::GlobalSettings::player_size);
  glVertex2d(y  * Settings::GlobalSettings::player_size,
             x  * Settings::GlobalSettings::player_size +
             Settings::GlobalSettings::player_size);

  // конец отрисовки полигона персонажа
  glEnd();
}

void Visualizer::StartPrint(int count) const // override by IMenu
{
}

void Visualizer::PrintRow(const std::vector<std::string>& names) const // override
                                                                       // by
                                                                       // IMenu
{
  glBegin(GL_POLYGON);

  for (int i = 0, j = 1; j < names.size() + 1; ++j)
  {
    std::cout << i << std::endl;

    int coord_hight  = 15;
    int coord_weight = 30;
    int size_of_str  = 2;

    glColor3f(1, 0, 0);                                          // RGB

    glVertex2d(coord_hight + i,  coord_hight + i);               // нижнний
                                                                 // левый
    glVertex2d(coord_hight + i,  coord_hight + size_of_str + i); // верхний
                                                                 // левый
    glVertex2d(coord_weight + i, coord_hight + size_of_str + i); // верхний
                                                                 // правый
    glVertex2d(coord_weight + i, coord_hight + i);               // нижний
                                                                 // правый
    i = i + 3;
  }
  glEnd();
}

void Visualizer::EndPrint() const // override by IMenu
{
}

std::size_t Visualizer::width() const // override byIMap
{
}

std::size_t Visualizer::height() const // override byIMap
{
}

const std::string& Visualizer::GetMap() const // override byIMap
{
}

void Visualizer::PrintMap(const std::string& map) const
{
  std::string my_map = map;

  for (int i = 0; i < Settings::GlobalSettings::window_height; ++i) // 25
  {
    int j = 0;

    for (; j < Settings::GlobalSettings::window_width; ++j) // 50
    {
      glBegin(GL_POLYGON);

      switch (my_map[(i * 25 + 1) + j])
      {
        case '#':
          glColor3f(0,   0,   1);
          break;
        case 'c':
          glColor3f(1,   0,   0);
          break;
        case 'm':
          glColor3f(0,   1,   0);
          break;
        case 's':
          glColor3f(1,   1,   0);
          break;
        case 'b':
          glColor3f(0.5, 0.5, 0.5);
          break;
      }
      glVertex2i(50 - j,      25 - i);
      glVertex2i(50 - j  + 1, 25 - i);
      glVertex2i(50 - j  + 1, 25 - i  + 1);
      glVertex2i(50 - j,      25 - i + 1);


      glEnd();
    }
    j = 0;
  }
}
} // Visual
