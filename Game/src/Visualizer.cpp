#include "Visualizer.hpp"

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

namespace Visual {
Visualizer::Visualizer(const Settings::GlobalSettings& settings)
  : settings_(settings)
  , menu_count_(0)
  , map_width_(0)
  , map_height_(0)
  , map_()
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

bool Visualizer::Show(const Player& player) //  передать
// вектор
// объектов
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

    //    std::string def_map = GetMap();
    //    PrintMap(def_map);

    player.show(); // отрисовка персонажа

    StartPrint(3);
    PrintRow("name1");
    PrintRow("name2");
    PrintRow("name3");
    EndPrint();


    glfwSwapBuffers(window_); // обмен буферов
    glfwPollEvents();         // обработчик событий, проверяет не зависло ли
                              // окно
  }

  while (!glfwWindowShouldClose(window_));

  return true;
}

void Visualizer::ShowPlayer(int x, int y) const // override by IPlayer
{
  // начало отрисовки полигона персонажа
  glBegin(GL_POLYGON);

  glColor3f(1, 1, 1); // RGB
  glVertex2d(x * settings_.player_size,
             y * settings_.player_size);
  glVertex2d(x * settings_.player_size + settings_.player_size,
             y * settings_.player_size);
  glVertex2d(x * settings_.player_size + settings_.player_size,
             y * settings_.player_size + settings_.player_size);
  glVertex2d(x * settings_.player_size,
             y * settings_.player_size + settings_.player_size);

  // конец отрисовки полигона персонажа
  glEnd();
}

void Visualizer::StartPrint(int count) // override by IMenu
{
  menu_count_ = count;
}

void Visualizer::PrintRow(const std::string& name) // override_by_IMenu
{
  std::string menu_map =
    "##################################################"
    "##################################################"
    "##################################################"
    "##################################################"
    "##################################################"
    "##################################################"
    "##################################################"
    "##################################################"
    "##################################################"
    "##################################################"
    "##################################################"
    "##################################################"
    "##################################################"
    "##################################################"
    "##################################################"
    "##################################################"
    "##################################################"
    "##################################################"
    "##################################################"
    "##################################################"
    "##################################################"
    "##################################################"
    "##################################################"
    "##################################################"
    "##################################################";

  int shift_of_line = 0; // сдвиг текста меню вправо относительно поля

  for (int i = 0; i < menu_count_; ++i)
  {
    for (unsigned long long k = 0; k < name.size(); ++k)
    {
      menu_map[shift_of_line + k] = 'n';
    }
    shift_of_line = shift_of_line + settings_.field_width * 2; // через строку
  }

  for (int i = 0; i < settings_.field_height; ++i)             // 25 вниз
  {
    int j = 0;

    for (; j < settings_.field_width; ++j) // 50 вбок
    {
      glBegin(GL_POLYGON);

      switch (menu_map[(i * 50) + j])
      {
        case '#':
          glColor3f(0, 0, 0);
          break;
        case 'n':
          glColor3f(1, 0, 0);
          break;
      }
      glVertex2f(0 +   j, 0  + (24 - i));
      glVertex2f(0 +   j, 1 +  (24 - i));
      glVertex2f(1 +   j, 1 +  (24 - i));
      glVertex2f(1 +   j, 0  + (24 - i));
      glEnd();
    }
    j = 0;
  }
}

void Visualizer::EndPrint() // override by IMenu
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

void Visualizer::PrintMap(const std::string& map) // override byIMap
{
  // settings_.field_height ==  height() from IMap
  // settings_.field_width == width() from IMap

  if (map.size() == settings_.map_lenght)            // длинна карты в символах
  {
    for (int i = 0; i < settings_.field_height; ++i) // 25 вниз
    {
      int j = 0;

      for (; j < settings_.field_width; ++j) // 50 вбок
      {
        glBegin(GL_POLYGON);

        switch (map[(i * 50) + j])
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
            glColor3f(1,   1,   1);
            break;
          case 'b':
            glColor3f(0.5, 0.5, 0.5);
            break;
        }
        glVertex2f(0 +   j, 0  + (24 - i));
        glVertex2f(0 +   j, 1 +  (24 - i));
        glVertex2f(1 +   j, 1 +  (24 - i));
        glVertex2f(1 +   j, 0  + (24 - i));
        glEnd();
      }
      j = 0;
    }
  }

  else {
    std::cout << "wrong map size" << std::endl;
  }
}
} // Visual
