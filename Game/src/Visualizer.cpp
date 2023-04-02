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

    menu.show();

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

  glColor3f(1, 0, 0);                                    // RGB
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

void Visualizer::StartPrint(int count) const
{
}

void Visualizer::PrintRow(const std::string& name) const
{
  // very debug version
  glBegin(GL_POLYGON);

  glColor3f(0, 1, 0);                                      // RGB
  glVertex2d(3 * Settings::GlobalSettings::menu_str_size,
             5 * Settings::GlobalSettings::menu_str_size); // вправо(x),
                                                           // вверх(y)
  glVertex2d(
    10  * Settings::GlobalSettings::menu_str_size + Settings::GlobalSettings::menu_str_size,
    5  * Settings::GlobalSettings::menu_str_size);
  glVertex2d(
    10  * Settings::GlobalSettings::menu_str_size + Settings::GlobalSettings::menu_str_size,
    5  * Settings::GlobalSettings::menu_str_size +
    Settings::GlobalSettings::menu_str_size);
  glVertex2d(3  * Settings::GlobalSettings::menu_str_size,
             5  * Settings::GlobalSettings::menu_str_size +
             Settings::GlobalSettings::menu_str_size);

  glEnd();
}

void Visualizer::EndPrint() const
{
}
} // Visual
