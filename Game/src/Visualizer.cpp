#include "Texture.hpp"
#include "MapTypes.hpp"
#include "Visualizer.hpp"

#include <cmath>
#include <stdexcept>

#define M_PI 3.14

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

void PrintTexture(Point  point,
                  size_t field_pixel,
                  GLuint textureID)
{
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, textureID);

  glColor3f(1, 1, 1);

  glBegin(GL_POLYGON);

  // 1.23

  glTexCoord2f(0, 0);
  glVertex2d(point.x * field_pixel, point.y * field_pixel);
  glTexCoord2f(1, 0);
  glVertex2d(point.x * field_pixel + field_pixel, point.y * field_pixel);
  glTexCoord2f(1, 1);
  glVertex2d(point.x * field_pixel + field_pixel,
             point.y * field_pixel + field_pixel);
  glTexCoord2f(0, 1);
  glVertex2d(point.x * field_pixel, point.y * field_pixel + field_pixel);

  glEnd();

  glDisable(GL_TEXTURE_2D);
}

void PrintTexture(Point  point,
                  size_t width,
                  size_t height,
                  size_t field_pixel,
                  GLuint textureID)
{
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  //glOrtho(0.0,   std::get<int>(settings_->GetValue("visual","window_width")
  //                             , 0.0,
  //                             std::get<int>(settings_->GetValue("visual", "window_height"), -1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();


  glLoadIdentity();
  glDisable(GL_LIGHTING);


  glColor3f(1,1,1);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, textureID);


  // Draw a textured quad
  glBegin(GL_QUADS);
  glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
  glTexCoord2f(0, 1); glVertex3f(0, 100, 0);
  glTexCoord2f(1, 1); glVertex3f(100, 100, 0);
  glTexCoord2f(1, 0); glVertex3f(100, 0, 0);
  glEnd();


  glDisable(GL_TEXTURE_2D);
  glPopMatrix();


  glMatrixMode(GL_PROJECTION);
  glPopMatrix();

  glMatrixMode(GL_MODELVIEW);
}
}

namespace Visual {
Visualizer::Visualizer(
  std::shared_ptr<Settings::ISettings>settings,
  std::shared_ptr<KeyManager>         keyManager)
  : menu_count_(0)
  , reverse_menu_count_(0)
  , player_vis_({ { 0, 0 }, 0 })
  ,  settings_(settings)
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

  LoeadTextures();
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

void Visualizer::PrintRow(const std::string& name, bool current) //
// override_by_IMenu
{
  const float where_down  = float(reverse_menu_count_ + reverse_menu_count_);
  const float where_right = 50;

  if (current) {
    glColor3f(1.f, 0, 0);
  } else {
    glColor3f(1.f, 1.f, 1.f);
  }

  func_print_char(name, where_down, where_right);
  reverse_menu_count_ += 60;
}

void Visualizer::EndPrint() // override by IMenu
{}

void Visualizer::ShowPlayer(Point          point,
                            PLAYER_STATE_X state_x,
                            PLAYER_STATE_Y state_y) {
  player_vis_.player_point = point;
  const double diff = player_vis_.player_point.x >
                      5 ? 5 : player_vis_.player_point.x;

  const int field_pixel =
    std::get<int>(settings_->GetValue("visual", "field_pixel"));
  std::string path;

  switch (state_y)
  {
    case (PLAYER_STATE_Y::FLY):
      PrintTexture(Point{ diff, player_vis_.player_point.y },
                   field_pixel,
                   textures_["mario-jump"].getId());
      return;

    case (PLAYER_STATE_Y::FALL):
      PrintTexture(Point{ diff, player_vis_.player_point.y },
                   field_pixel,
                   textures_["mario-fall"].getId());
      return;
  }

  switch (state_x)
  {
    case (PLAYER_STATE_X::STAND):
      PrintTexture(Point{ diff, player_vis_.player_point.y },
                   field_pixel,
                   textures_["mario"].getId());
      return;

    case (PLAYER_STATE_X::RUN_RIGHT):
      PrintTexture(Point{ diff, player_vis_.player_point.y },
                   field_pixel,
                   textures_["mario-run" +
                             std::to_string(player_vis_.player_frame_)].getId());

      ++player_vis_.player_frame_;

      if (player_vis_.player_frame_ > 2)
      {
        player_vis_.player_frame_ = 0;
      }
      return;

    case (PLAYER_STATE_X::RUN_LEFT):
      PrintTexture(Point{ diff, player_vis_.player_point.y },
                   field_pixel,
                   textures_["mario-run-left" +
                             std::to_string(player_vis_.player_frame_)].getId());

      ++player_vis_.player_frame_;

      if (player_vis_.player_frame_ > 2)
      {
        player_vis_.player_frame_ = 0;
      }
      return;
  }
}

void Visualizer::PrintBlock(Point point, int type)
{
  const int diff = point.x - static_cast<int>(player_vis_.player_point.x);

  if ((diff > 10) || (diff < 0)) {
    return;
  }

  const int field_pixel = std::get<int>(settings_->GetValue("visual",
                                                            "field_pixel"));
  std::string name;

  switch (type) {
    case BLOCK:
      name = "block";
      break;
    case COIN:
      name = "coin";
      break;
    case PIPE:
      name = "pipe";
      break;
    case MUSHROOOM:
      name = "mushroom";
      break;
    case STEPBLOCK:
      name = "stepblock";
      break;
    case GROUND:
      name = "ground";
      break;
    case SKY:
      name = "sky";
      break;
    case CLOUD:
      name = "cloud";
      break;
  }

  PrintTexture(Point{ static_cast<double>(diff), point.y },
               field_pixel,
               textures_[name].getId());
}

void Visualizer::ShowScore(int score)
{
  int y = 7;

  glBegin(GL_POLYGON);

  if (score == 0) glColor3f(1, 1, 1);  // for debug

  if (score == 1) glColor3f(0, 1, 0);  // for debug

  if (score == 2) glColor3f(0, 1, 1);  // for debug

  if (score > 2) glColor3f(1, 0, 0);   // for debug

  const int field_pixel = std::get<int>(settings_->GetValue("visual",
                                                            "field_pixel"));

  glVertex2d(0,
             y * field_pixel);
  glVertex2d(0 + field_pixel,
             y * field_pixel);
  glVertex2d(0 + field_pixel,
             y * field_pixel + field_pixel);
  glVertex2d(0,
             y * field_pixel + field_pixel);
  glEnd();

  const float where_down  = -79;
  const float where_right = 70;

  glColor3f(1.f, 1.f, 1.f);
  func_print_char("coins", where_down, where_right);
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
          std::get<int>(settings_->GetValue("visual",
                                            "window_height")),
          1,
          0);

  glClearColor(0.15f, 0.46f, 0.46f, 1.0f);

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

void Visualizer::LoeadTextures()
{
  auto getPath = [this](const char *name)
                 {
                   return "../Game/" + std::get<std::string>(settings_->GetValue(
                                                               "textures",
                                                               name));
                 };

  textures_["mario"]      = Textures::Texture(getPath("mario").c_str());
  textures_["mario-jump"] =
    Textures::Texture(getPath("mario-jump").c_str());
  textures_["mario-fall"] =
    Textures::Texture(getPath("mario-fall").c_str());
  textures_["mario-run0"] =
    Textures::Texture(getPath("mario-run0").c_str());
  textures_["mario-run1"] =
    Textures::Texture(getPath("mario-run1").c_str());
  textures_["mario-run2"] =
    Textures::Texture(getPath("mario-run2").c_str());
  textures_["mario-run-left0"] = Textures::Texture(getPath(
                                                     "mario-run-left0").c_str());
  textures_["mario-run-left1"] = Textures::Texture(getPath(
                                                     "mario-run-left1").c_str());
  textures_["mario-run-left2"] = Textures::Texture(getPath(
                                                     "mario-run-left2").c_str());
  textures_["block"]     = Textures::Texture(getPath("block").c_str());
  textures_["coin"]      = Textures::Texture(getPath("coin").c_str());
  textures_["pipe"]      = Textures::Texture(getPath("pipe").c_str());
  textures_["mushroom"]  = Textures::Texture(getPath("mushroom").c_str());
  textures_["stepblock"] =
    Textures::Texture(getPath("stepblock").c_str());
  textures_["ground"] = Textures::Texture(getPath("ground").c_str());
  textures_["sky"]    = Textures::Texture(getPath("sky").c_str());
  textures_["cloud"]  = Textures::Texture(getPath("cloud").c_str());
  textures_["symbols"] =
    Textures::Texture(getPath("symbols").c_str());
  textures_["menu-bg"] =
    Textures::Texture(getPath("menu-bg").c_str());
}

void Visualizer::func_print_char(const std::string name,
                                 const float       where_down,
                                 const float       where_right)
{
  unsigned long long i = 0;
  float space          = 0;
  int   coord          = 400;

  for (; i < name.size();)
  {
    while (name[i] != *name.end())
    {
      if ((name[i] == 'a') || (name[i] == 'A'))
      {
        glBegin(GL_LINE_LOOP);
        float a1 = where_down;
        float a2 = where_right + float(i) + space;
        glVertex2f(0 +      a2,  0  +  (coord - 50 - a1));
        glVertex2f(30 +    a2,   50 + (coord - 50 - a1));
        glVertex2f(50 +      a2, 0  +  (coord - 50 - a1));
        glVertex2f(30 +    a2,   50 + (coord - 50 - a1));
        glVertex2f(0 +      a2,  0  +  (coord - 50 - a1));
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex2f(15 +   a2, 30 +  (coord - 50 - a1));
        glVertex2f(45 +   a2, 30  + (coord - 50 - a1));
        glEnd();
        ++i;
        space += 60;
        continue;
      }

      if ((name[i] == 'b') || (name[i] == 'B'))
      {
        float b1 = where_down;
        float b2 = where_right + float(i) + space;
        glBegin(GL_LINE_LOOP);
        glVertex2f(0 +   b2,  0  +  (coord - 50 - b1));
        glVertex2f(0 +   b2,  50 +  (coord - 50 - b1));
        glVertex2f(50 +   b2, 50 +  (coord - 50 -  b1));
        glVertex2f(50 +   b2, 42 + (coord - 50 - b1));
        glVertex2f(36 +  b2,  36  + (coord - 50 - b1));
        glVertex2f(50 +   b2, 24  + (coord - 50 - b1));
        glVertex2f(50 +   b2, 0  + (coord - 50 - b1));
        glVertex2f(0 +   b2,  0  + (coord - 50 - b1));
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex2f(36 +  b2, 36  + (coord - 50 - b1));
        glVertex2f(0 +   b2, 36  + (coord - 50 - b1));
        glEnd();
        ++i;
        space += 60;
        continue;
      }

      if ((name[i] == 'c') || (name[i] == 'C'))
      {
        float c1 = where_down;
        float c2 = where_right + float(i) + space;
        glBegin(GL_LINE_LOOP);
        glVertex2f(0 +   c2,  0  + (coord - 50 - c1));
        glVertex2f(0 +   c2,  50 + (coord - 50 - c1));
        glVertex2f(50 +   c2, 50 + (coord - 50 -  c1));
        glVertex2f(0 +   c2,  50 + (coord - 50 - c1));
        glVertex2f(0 +   c2,  0  + (coord - 50 - c1));
        glVertex2f(50 +   c2, 0 + (coord - 50 -  c1));
        glEnd();
        ++i;
        space += 60;
        continue;
      }

      if ((name[i] == 'd') || (name[i] == 'D'))
      {
        float d1 = where_down;
        float d2 = where_right + float(i) + space;
        glBegin(GL_LINE_LOOP);
        glVertex2f(0 +   d2,  0  + (coord - 50 - d1));
        glVertex2f(0 +   d2,  50 +  (coord - 50 - d1));
        glVertex2f(50 +   d2, 50 +  (coord - 50 - d1));
        glVertex2f(50 +   d2, 0  + (coord - 50 - d1));
        glEnd();
        ++i;
        space += 60;
        continue;
      }

      if ((name[i] == 'e') || (name[i] == 'E'))
      {
        float e1 = where_down;
        float e2 = where_right + float(i) + space;
        glBegin(GL_LINE_LOOP);
        glVertex2f(0 +   e2,  0  + (coord - 50 - e1));
        glVertex2f(0 +   e2,  50 + (coord - 50 - e1));
        glVertex2f(50 +   e2, 50 + (coord - 50 -  e1));
        glVertex2f(0 +   e2,  50 + (coord - 50 - e1));
        glVertex2f(0 +   e2,  0  + (coord - 50 - e1));
        glVertex2f(50 +   e2, 0 + (coord - 50 -  e1));
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex2f(0 +   e2, 30  + (coord - 50 - e1));
        glVertex2f(30 +  e2, 30  + (coord - 50 - e1));
        glEnd();
        ++i;
        space += 60;
        continue;
      }

      if ((name[i] == 'f') || (name[i] == 'F'))
      {
        float f1 =  where_down;
        float f2 =  where_right + float(i) + space;
        glBegin(GL_LINE_LOOP);
        glVertex2f(0 +   f2,  0  + (coord - 50 - f1));
        glVertex2f(0 +   f2,  50 + (coord - 50 - f1));
        glVertex2f(50 +   f2, 50 + (coord - 50 -  f1));
        glVertex2f(0 +   f2,  50 + (coord - 50 - f1));
        glVertex2f(0 +   f2,  0  + (coord - 50 - f1));
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex2f(0 +   f2, 30  + (coord - 50 - f1));
        glVertex2f(30 + f2,  30  + (coord - 50 - f1));
        glEnd();
        ++i;
        space += 60;
        continue;
      }

      if ((name[i] == 'g') || (name[i] == 'G'))
      {
        float g1 =  where_down;
        float g2 =  where_right + float(i) + space;
        glBegin(GL_LINE_LOOP);
        glVertex2f(0 +   g2,  0  + (coord - 50 - g1));
        glVertex2f(0 +   g2,  50 + (coord - 50 - g1));
        glVertex2f(50 +   g2, 50 + (coord - 50 -  g1));
        glVertex2f(0 +   g2,  50 + (coord - 50 - g1));
        glVertex2f(0 +   g2,  0  + (coord - 50 - g1));
        glVertex2f(50 +   g2, 0 + (coord - 50 -  g1));
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex2f(50 +   g2, 0 + (coord - 50 -  g1));
        glVertex2f(50 +   g2, 30 + (coord - 50 -  g1));
        glVertex2f(36 +   g2, 30 + (coord - 50 -  g1));
        glVertex2f(36 +   g2, 12 + (coord - 50 -  g1));
        glVertex2f(36 +   g2, 30 + (coord - 50 -  g1));
        glVertex2f(50 +   g2, 30 + (coord - 50 -  g1));
        glVertex2f(50 +   g2, 0 + (coord - 50 -  g1));
        glEnd();
        ++i;
        space += 60;
        continue;
      }

      if ((name[i] == 'h') || (name[i] == 'H'))
      {
        float h1 =   where_down;
        float h2 =   where_right + float(i) + space;
        glBegin(GL_LINE_LOOP);
        glVertex2f(0 +   h2, 0  + (coord - 50 - h1));
        glVertex2f(0 +   h2, 50 +  (coord - 50 - h1));
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex2f(50 +   h2, 0  + (coord - 50 - h1));
        glVertex2f(50 +   h2, 50 + (coord - 50 - h1));
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex2f(0 +   h2,  30  + (coord - 50 - h1));
        glVertex2f(50 +   h2, 30  + (coord - 50 - h1));
        glEnd();
        ++i;
        space += 60;
        continue;
      }

      if ((name[i] == 'i') || (name[i] == 'I'))
      {
        float i1 =  where_down;
        float i2 =  where_right + float(i) + space;
        glBegin(GL_LINE_LOOP);
        glVertex2f(25 +   i2, 50 + (coord - 50 - i1));
        glVertex2f(25 +   i2, 50 +  (coord - 50 - i1));
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex2f(25 +   i2, 0  + (coord - 50 - i1));
        glVertex2f(25 +   i2, 0  + (coord - 50 - i1));
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex2f(25 +   i2, 50 + (coord - 50 - i1));
        glVertex2f(25 +   i2, 0  + (coord - 50 - i1));
        glEnd();
        ++i;
        space += 60;
        continue;
      }

      if ((name[i] == 'j') || (name[i] == 'J'))
      {
        float j1 =  where_down;
        float j2 =  where_right + float(i) + space;
        glBegin(GL_LINE_LOOP);
        glVertex2f(50 +   j2, 50 + (coord - 50 - j1));
        glVertex2f(50 +   j2, 0 +  (coord - 50 - j1));
        glVertex2f(0 +   j2,  0  + (coord - 50 - j1));
        glVertex2f(0 +   j2,  24  + (coord - 50 - j1));
        glVertex2f(24 +   j2, 24  + (coord - 50 - j1));
        glVertex2f(0 +   j2,  24  + (coord - 50 - j1));
        glVertex2f(0 +   j2,  0  + (coord - 50 - j1));
        glVertex2f(50 +   j2, 0 +  (coord - 50 - j1));
        glEnd();
        ++i;
        space += 60;
        continue;
      }

      if ((name[i] == 'k') || (name[i] == 'K'))
      {
        float k1 =  where_down;
        float k2 =  where_right + float(i) + space;
        glBegin(GL_LINE_LOOP);
        glVertex2f(0 +   k2, 0  + (coord - 50 - k1));
        glVertex2f(0 +   k2, 50 +  (coord - 50 - k1));
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex2f(0 +   k2,  30  + (coord - 50 - k1));
        glVertex2f(50 +   k2, 50 + (coord - 50 - k1));
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex2f(0 +   k2,  30  + (coord - 50 - k1));
        glVertex2f(50 +   k2, 0  + (coord - 50 - k1));
        glEnd();
        ++i;
        space += 60;
        continue;
      }

      if ((name[i] == 'l') || (name[i] == 'L'))
      {
        float l1 =  where_down;
        float l2 =  where_right + float(i) + space;
        glBegin(GL_LINE_LOOP);
        glVertex2f(0 +   l2,  0  + (coord - 50 - l1));
        glVertex2f(0 +   l2,  50 +  (coord - 50 - l1));
        glVertex2f(0 +   l2,  0  + (coord - 50 - l1));
        glVertex2f(50 +   l2, 0  + (coord - 50 - l1));
        glEnd();
        ++i;
        space += 60;
        continue;
      }

      if ((name[i] == 'm') || (name[i] == 'M'))
      {
        float m1 =  where_down;
        float m2 =  where_right + float(i) + space;
        glBegin(GL_LINE_LOOP);
        glVertex2f(0 +   m2, 0  + (coord - 50 - m1));
        glVertex2f(0 +   m2, 50 +  (coord - 50 - m1));
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex2f(50 +   m2, 0  + (coord - 50 - m1));
        glVertex2f(50 +   m2, 50 + (coord - 50 - m1));
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex2f(50 +   m2, 50 + (coord - 50 - m1));
        glVertex2f(30 +   m2, 42  + (coord - 50 - m1));
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex2f(0 +   m2,  50 + (coord - 50 - m1));
        glVertex2f(30 +   m2, 42  + (coord - 50 - m1));
        glEnd();
        ++i;
        space += 60;
        continue;
      }

      if ((name[i] == 'n') || (name[i] == 'N'))
      {
        float n1 =  where_down;
        float n2 =  where_right + float(i) + space;
        glBegin(GL_LINE_LOOP);
        glVertex2f(0 +   n2, 0  + (coord - 50 - n1));
        glVertex2f(0 +   n2, 50 +  (coord - 50 - n1));
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex2f(50 +   n2, 0  + (coord - 50 - n1));
        glVertex2f(50 +   n2, 50 + (coord - 50 - n1));
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex2f(0 +   n2,  50 + (coord - 50 - n1));
        glVertex2f(50 +   n2, 0  + (coord - 50 - n1));
        glEnd();
        ++i;
        space += 60;
        continue;
      }

      if ((name[i] == 'o') || (name[i] == 'o'))
      {
        float o1         =  where_down;
        float o2         =  where_right + float(i) + space;
        float xCenter    = 25 + o2;
        float yCenter    = coord - 25 - o1;
        float rx         = 25;
        float ry         = 25;
        float angle      = 0;
        const float step = float(2 * M_PI / 360);
        glBegin(GL_LINE_STRIP);

        for (int j = 0; j < 360; ++j)
        {
          const float dx = rx * cosf(angle);
          const float dy = ry * sinf(angle);
          glVertex2f(dx + xCenter, dy + yCenter);
          angle += step;
        }
        glEnd();
        ++i;
        space += 60;
        continue;
      }

      if ((name[i] == 'p') || (name[i] == 'P'))
      {
        float p1 =  where_down;
        float p2 =  where_right + float(i) + space;
        glBegin(GL_LINE_LOOP);
        glVertex2f(0 +   p2,  0  + (coord - 50 - p1));
        glVertex2f(0 +   p2,  50 +  (coord - 50 - p1));
        glVertex2f(50 +   p2, 50 + (coord - 50 - p1));
        glVertex2f(50 +   p2, 30  + (coord - 50 - p1));
        glVertex2f(0 +   p2,  30  + (coord - 50 - p1));
        glVertex2f(0 +   p2,  0  + (coord - 50 - p1));
        glEnd();
        ++i;
        space += 60;
        continue;
      }

      if ((name[i] == 'q') || (name[i] == 'Q'))
      {
        float q1           = where_down;
        float q2           = where_right + float(i) + space;
        float q_xCenter    = 25 + q2;
        float q_yCenter    = coord - 25 - q1;
        float q_rx         = 25;
        float q_ry         = 25;
        float q_angle      = 0;
        const float q_step = float(2 * M_PI / 360);
        glBegin(GL_LINE_STRIP);

        for (int i = 0; i < 360; ++i)
        {
          const float q_dx = q_rx * cosf(q_angle);
          const float q_dy = q_ry * sinf(q_angle);
          glVertex2f(q_dx + q_xCenter, q_dy + q_yCenter);
          q_angle += q_step;
        }
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex2f(50 +   q2, 0  + (coord - 50 - q1));
        glVertex2f(25 +   q2, 12  + (coord - 50 - q1));
        glEnd();
        ++i;
        space += 60;
        continue;
      }

      if ((name[i] == 'r') || (name[i] == 'r'))
      {
        float r1 = where_down;
        float r2 = where_right + float(i) + space;
        glBegin(GL_LINE_LOOP);
        glVertex2f(0 +   r2,  0  + (coord - 50 - r1));
        glVertex2f(0 +   r2,  50 +  (coord - 50 - r1));
        glVertex2f(50 +   r2, 50 + (coord - 50 - r1));
        glVertex2f(50 +   r2, 30  + (coord - 50 - r1));
        glVertex2f(0 +   r2,  30  + (coord - 50 - r1));
        glVertex2f(50 +   r2, 0  + (coord - 50 - r1));
        glVertex2f(0 +   r2,  30  + (coord - 50 - r1));
        glVertex2f(0 +   r2,  0  + (coord - 50 - r1));
        glEnd();
        ++i;
        space += 60;
        continue;
      }

      if ((name[i] == 's') || (name[i] == 'S'))
      {
        float s1 =  where_down;
        float s2 =  where_right + float(i) + space;
        glBegin(GL_LINE_LOOP);
        glVertex2f(0 +   s2,  0  + (coord - 50 -   s1));
        glVertex2f(50 +   s2, 0 +  (coord - 50 -   s1));
        glVertex2f(50 +   s2, 30  + (coord - 50 -   s1));
        glVertex2f(0 +   s2,  30  + (coord - 50 -   s1));
        glVertex2f(0 +   s2,  50 + (coord - 50 - s1));
        glVertex2f(50 +   s2, 50 + (coord - 50 - s1));
        glVertex2f(0 +   s2,  50 + (coord - 50 - s1));
        glVertex2f(0 +   s2,  30  + (coord - 50 -   s1));
        glVertex2f(50 +   s2, 30  + (coord - 50 -   s1));
        glVertex2f(50 +   s2, 0 +  (coord - 50 -   s1));
        glEnd();
        ++i;
        space += 60;
        continue;
      }

      if ((name[i] == 't') || (name[i] == 'T'))
      {
        float t1 =  where_down;
        float t2 =  where_right + float(i) + space;
        glBegin(GL_LINE_LOOP);
        glVertex2f(0 +   t2,  50 + (coord - 50 - t1));
        glVertex2f(50 +   t2, 50 +  (coord - 50 - t1));
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex2f(30 +   t2, 50 + (coord - 50 - t1));
        glVertex2f(30 +   t2, 0  + (coord - 50 - t1));
        glEnd();
        ++i;
        space += 60;
        continue;
      }

      if ((name[i] == 'u') || (name[i] == 'U'))
      {
        float u1 = where_down;
        float u2 = where_right + float(i) + space;
        glBegin(GL_LINE_LOOP);
        glVertex2f(0 +   u2, 0  + (coord - 50 - u1));
        glVertex2f(0 +   u2, 50 +  (coord - 50 - u1));
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex2f(50 +   u2, 0  + (coord - 50 - u1));
        glVertex2f(50 +   u2, 50 + (coord - 50 - u1));
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex2f(0 +   u2,  0  + (coord - 50 - u1));
        glVertex2f(50 +   u2, 0  + (coord - 50 - u1));
        glEnd();
        ++i;
        space += 60;
        continue;
      }

      if ((name[i] == 'v') || (name[i] == 'V'))
      {
        float v1 =  where_down;
        float v2 =  where_right + float(i) + space;
        glBegin(GL_LINE_LOOP);
        glVertex2f(0 +   v2, 50 + (coord - 50 - v1));
        glVertex2f(30 + v2,  0 +  (coord - 50 - v1));
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex2f(30 +   v2, 0  + (coord - 50 - v1));
        glVertex2f(50 +   v2, 50 + (coord - 50 - v1));
        glEnd();
        ++i;
        space += 60;
        continue;
      }

      if ((name[i] == 'w') || (name[i] == 'W'))
      {
        float w1 =  where_down;
        float w2 =  where_right + float(i) + space;
        glBegin(GL_LINE_LOOP);
        glVertex2f(0 +   w2,  50 + (coord - 50 - w1));
        glVertex2f(12 +   w2, 0 +  (coord - 50 - w1));
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex2f(12 +   w2, 0  + (coord - 50 - w1));
        glVertex2f(30 +   w2, 30  + (coord - 50 - w1));
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex2f(30 +   w2,  30  + (coord - 50 - w1));
        glVertex2f(0.8 +   w2, 0  + (coord - 50 - w1));
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex2f(0.8 +   w2, 0  + (coord - 50 - w1));
        glVertex2f(50 +   w2,  50 + (coord - 50 - w1));
        glEnd();
        ++i;
        space += 60;
        continue;
      }

      if ((name[i] == 'x') || (name[i] == 'X'))
      {
        float x1 =  where_down;
        float x2 =  where_right + float(i) + space;
        glBegin(GL_LINE_LOOP);
        glVertex2f(0 +   x2, 50 + (coord - 50 - x1));
        glVertex2f(50 + x2,  0 +  (coord - 50 - x1));
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex2f(0 +   x2,  0  + (coord - 50 - x1));
        glVertex2f(50 +   x2, 50 + (coord - 50 - x1));
        glEnd();
        ++i;
        space += 60;
        continue;
      }

      if ((name[i] == 'y') || (name[i] == 'Y'))
      {
        float y1 =  where_down;
        float y2 =  where_right + float(i) + space;
        glBegin(GL_LINE_LOOP);
        glVertex2f(0 +  y2, 50 + (coord - 50 - y1));
        glVertex2f(30 + y2, 30 +  (coord - 50 - y1));
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex2f(50 +  y2, 50 + (coord - 50 - y1));
        glVertex2f(30 + y2,  30 +  (coord - 50 - y1));
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex2f(30 +   y2, 30  + (coord - 50 - y1));
        glVertex2f(30 +   y2, 0  + (coord - 50 - y1));
        glEnd();
        ++i;
        space += 60;
        continue;
      }

      if ((name[i] == 'z') || (name[i] == 'Z'))
      {
        float z1 =  where_down;
        float z2 =  where_right + float(i) + space;
        glBegin(GL_LINE_LOOP);
        glVertex2f(0 +  z2, 50 + (coord - 50 - z1));
        glVertex2f(50 + z2, 50 +  (coord - 50 - z1));
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex2f(50 +   z2, 50 + (coord - 50 - z1));
        glVertex2f(0 +   z2,  0  + (coord - 50 - z1));
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex2f(0 +   z2,  0 + (coord - 50 - z1));
        glVertex2f(50 +   z2, 0  + (coord - 50 - z1));
        glEnd();
        ++i;
        space += 60;
        continue;
      }

      if  (name[i] == ' ')
      {
        ++i;
        space += 30;
        continue;
      }

      if  (!isalpha(name[i]))
      {
        throw std::invalid_argument("not text simbol");
        continue;
      }
    }
  }
}
} // Visual
