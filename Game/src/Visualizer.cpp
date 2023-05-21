#include "Texture.hpp"
#include "MapTypes.hpp"
#include "Visualizer.hpp"
#include "stb_easy_font.h"

#include <cmath>
#include <stdexcept>

namespace {
Visual::Visualizer *rawPtr = nullptr;
void KeyCatch(GLFWwindow *, int key, int scancode, int action, int mods)
{
  rawPtr->KeyCatch(key,
                   scancode,
                   action,
                   mods);
}

void framebuffer_size_callback_(GLFWwindow *, int width, int height) {
  glViewport(0, 0, width, height);
}

void PrintTexture(double x, double y, int field_pixel, const std::string& path)
{
  GLuint TextureID;

  Textures::Texture::LoadTexture(
    path.c_str(),
    &TextureID,
    GL_REPEAT,
    GL_NEAREST,
    NULL);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, TextureID);

  glColor3f(1, 1, 1);

  glBegin(GL_POLYGON);

  glTexCoord2f(0, 0);
  glVertex2d(x, -y * field_pixel);
  glTexCoord2f(1, 0);
  glVertex2d(x + field_pixel, -y * field_pixel);
  glTexCoord2f(1, 1);
  glVertex2d(x + field_pixel, -y * field_pixel - field_pixel);
  glTexCoord2f(0, 1);
  glVertex2d(x, -y * field_pixel - field_pixel);

  glEnd();

  glDisable(GL_TEXTURE_2D);
}
}

namespace Visual {
Visualizer::Visualizer(
  std::shared_ptr<Settings::ISettings>settings,
  std::shared_ptr<KeyManager>         keyManager)
  : menu_count_(0)
  , reverse_menu_count_(0)
  , player_x(0)
  , player_y(0)
  , settings_(settings)
  , keyManager_(std::move(keyManager))

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

  rawPtr = this;
  glfwSetKeyCallback(window_, ::KeyCatch);
  glfwSetFramebufferSizeCallback(window_, ::framebuffer_size_callback_);
}

Visualizer::~Visualizer()
{
  glfwTerminate();
}

void Visualizer::StartPrint(int count) // override by IMenu
{
  menu_count_         = count;
  reverse_menu_count_ = 1;
}

void print_string(float x, float y, char *text, float r, float g, float b)
{
  static char buffer[99999]; // ~500 chars
  int num_quads;

  num_quads = stb_easy_font_print(x, y, text, NULL, buffer, sizeof(buffer));

  glColor3f(r, g, b);
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(2, GL_FLOAT, 16, buffer);
  glDrawArrays(GL_QUADS, 0, num_quads * 4);
  glDisableClientState(GL_VERTEX_ARRAY);
}

// override_by_IMenu
void Visualizer::PrintRow(const std::string& name, bool current)
{
  float r = 0;
  float g = 0;
  float b = 0;

  if (current) {
    r = 1.f;
  }
  else {
    r = 1.f;
    g = 1.f;
    b = 1.f;
  }

  print_string(160,
               -400 - reverse_menu_count_,
               const_cast<char *>(name.c_str()),
               r,
               g,
               b);
  reverse_menu_count_ -= 60;
}

void Visualizer::EndPrint() // override by IMenu
{
}

void Visualizer::ShowPlayer(double x, double y) {
  player_x = x;
  player_y = y;
  const int field_pixel = std::get<int>(settings_->GetValue("visual",
                                                            "field_pixel"));
  const std::string path = "../Game/" +
                           std::get<std::string>(settings_->GetValue("textures",
                                                                     "mario"));

  PrintTexture(player_x, player_y, field_pixel, path);
}

void Visualizer::PrintBlock(size_t x, size_t y, int type)
{
  const int diff = x - player_x;

  if ((diff > 10) || (diff < 0)) {
    return;
  }

  const int field_pixel = std::get<int>(settings_->GetValue("visual",
                                                            "field_pixel"));
  std::string path;

  switch (type) {
    case BLOCK:
      path = "../Game/" + std::get<std::string>(settings_->GetValue("textures",
                                                                    "block"));
      break;
    case COIN:
      path = "../Game/" + std::get<std::string>(settings_->GetValue("textures",
                                                                    "coin"));
      break;
    case PIPE:
      path = "../Game/" + std::get<std::string>(settings_->GetValue("textures",
                                                                    "pire"));
      break;
    case MUSHROOOM:
      path = "../Game/" + std::get<std::string>(settings_->GetValue("textures",
                                                                    "mushroom"));
      break;
    case STEPBLOCK:
      path = "../Game/" + std::get<std::string>(settings_->GetValue("textures",
                                                                    "stepblock"));
      break;
    case GROUND:
      path = "../Game/" + std::get<std::string>(settings_->GetValue("textures",
                                                                    "ground"));
      break;
  }

  PrintTexture(diff * field_pixel, y, field_pixel, path);
}

void Visualizer::ShowScore(int score)
{
  std::string str_score = std::to_string(score);

  print_string(0,  -480, const_cast<char *>(str_score.c_str()), 1, 1, 1);
  print_string(10, -480, "coins",                               1, 1, 1);
}

bool Visualizer::Show(const std::vector<std::shared_ptr<IEntity> >& dataToShow)
{
  if (glfwWindowShouldClose(window_))
  {
    return false;
  }

  glLoadIdentity();             // считывает текущую матрицу
  glClear(GL_COLOR_BUFFER_BIT); // очистка буфера
  glOrtho(0,
          std::get<int>(settings_->GetValue("visual",
                                            "window_width")),
          0,
          -std::get<int>(settings_->GetValue("visual",
                                             "window_height")),
          1,
          0);

  for (const auto& el: dataToShow) {
    el->onRender();
  }

  glfwSwapBuffers(window_); // обмен буферов
  glfwPollEvents();         // обработчик событий, проверяет не зависло ли
                            // окно
  return true;
}

void Visualizer::KeyCatch(int key, int scancode, int action, int mods)
{
  rawPtr->keyManager_->KeyAction(key, scancode,
                                 static_cast<KeyManager::KEY_ACTION>(action),
                                 mods);
}
} // Visual
