#include "Visualizer.hpp"

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
}

namespace Visual {
Visualizer::Visualizer(
  std::shared_ptr<Settings::ISettings>settings,
  std::shared_ptr<KeyManager>         keyManager)
  : menu_count_(0)
  , reverse_menu_count_(0)
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
  // рисование текста
  if (reverse_menu_count_ <= menu_count_)
  {
    const float where_down  = float(reverse_menu_count_ + reverse_menu_count_);
    const float where_right = 1;

    if (current) {
      glColor3f(1.f, 0, 0);
    } else {
      glColor3f(1.f, 1.f, 1.f);
    }

    func_print_char(name, where_down, where_right);
    ++reverse_menu_count_;
  }
}

void Visualizer::EndPrint() // override by IMenu
{}

void Visualizer::ShowPlayer(int x, int y)
{
  // начало отрисовки полигона персонажа
  glBegin(GL_POLYGON);

  glColor3f(1, 1, 1); // RGB
  const int player_size = std::get<int>(settings_->GetValue("visual",
                                                            "player_size"));

  glVertex2d(x * player_size,
             y * player_size);
  glVertex2d(x * player_size + player_size,
             y * player_size);
  glVertex2d(x * player_size + player_size,
             y * player_size + player_size);
  glVertex2d(x * player_size,
             y * player_size + player_size);

  // конец отрисовки полигона персонажа
  glEnd();
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
                                            "field_width")),
          0,
          std::get<int>(settings_->GetValue("visual",
                                            "field_height")),
          0,
          10);

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

void Visualizer::func_print_char(const std::string name,
                                 const float       where_down,
                                 const float       where_right)
{
  unsigned long long i = 0;
  float space          = 0;

  for (; i < name.size();)
  {
    while (name[i] != *name.end())
    {
      if ((name[i] == 'a') || (name[i] == 'A'))
      {
        glBegin(GL_LINE_LOOP);

        float a1 = where_down;
        float a2 = where_right + float(i) + space;
        glVertex2f(0 +      a2, 0  + (24 - a1));
        glVertex2f(0.5 +    a2, 1  + (24 - a1));
        glVertex2f(1 +      a2, 0  + (24 - a1));
        glVertex2f(0.5 +    a2, 1  + (24 - a1));
        glVertex2f(0 +      a2, 0  + (24 - a1));
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex2f(0.25 +   a2, 0.5 +  (24 - a1));
        glVertex2f(0.75 +   a2, 0.5  + (24 - a1));
        glEnd();
        ++i;
        space += 0.3;
        continue;
      }

      if ((name[i] == 'b') || (name[i] == 'B'))
      {
        float b1 = where_down;
        float b2 = where_right + float(i) + space;
        glBegin(GL_LINE_LOOP);
        glVertex2f(0 +   b2,  0  +  (24 - b1));
        glVertex2f(0 +   b2,  1  +  (24 - b1));
        glVertex2f(1 +   b2,  1 +  (24 -  b1));
        glVertex2f(1 +   b2,  0.7 + (24 - b1));
        glVertex2f(0.6 +  b2, 0.6  + (24 - b1));
        glVertex2f(1 +   b2,  0.4  + (24 - b1));
        glVertex2f(1 +   b2,  0  + (24 - b1));
        glVertex2f(0 +   b2,  0  + (24 - b1));
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex2f(0.6 +  b2, 0.6  + (24 - b1));
        glVertex2f(0 +   b2,  0.6  + (24 - b1));
        glEnd();
        ++i;
        space += 0.3;
        continue;
      }

      if ((name[i] == 'c') || (name[i] == 'C'))
      {
        float c1 = where_down;
        float c2 = where_right + float(i) + space;
        glBegin(GL_LINE_LOOP);
        glVertex2f(0 +   c2, 0  + (24 - c1));
        glVertex2f(0 +   c2, 1  + (24 - c1));
        glVertex2f(1 +   c2, 1 + (24 -  c1));
        glVertex2f(0 +   c2, 1  + (24 - c1));
        glVertex2f(0 +   c2, 0  + (24 - c1));
        glVertex2f(1 +   c2, 0 + (24 -  c1));
        glEnd();
        ++i;
        space += 0.3;
        continue;
      }

      if ((name[i] == 'd') || (name[i] == 'D'))
      {
        float d1 = where_down;
        float d2 = where_right + float(i) + space;
        glBegin(GL_LINE_LOOP);
        glVertex2f(0 +   d2, 0  + (24 - d1));
        glVertex2f(0 +   d2, 1 +  (24 - d1));
        glVertex2f(1 +   d2, 1 +  (24 - d1));
        glVertex2f(1 +   d2, 0  + (24 - d1));
        glEnd();
        ++i;
        space += 0.3;
        continue;
      }

      if ((name[i] == 'e') || (name[i] == 'E'))
      {
        float e1 = where_down;
        float e2 = where_right + float(i) + space;
        glBegin(GL_LINE_LOOP);
        glVertex2f(0 +   e2, 0  + (24 - e1));
        glVertex2f(0 +   e2, 1  + (24 - e1));
        glVertex2f(1 +   e2, 1 + (24 -  e1));
        glVertex2f(0 +   e2, 1  + (24 - e1));
        glVertex2f(0 +   e2, 0  + (24 - e1));
        glVertex2f(1 +   e2, 0 + (24 -  e1));
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex2f(0 +   e2,  0.5  + (24 - e1));
        glVertex2f(0.5 +  e2, 0.5  + (24 - e1));
        glEnd();
        ++i;
        space += 0.3;
        continue;
      }

      if ((name[i] == 'f') || (name[i] == 'F'))
      {
        float f1 =  where_down;
        float f2 =  where_right + float(i) + space;
        glBegin(GL_LINE_LOOP);
        glVertex2f(0 +   f2, 0  + (24 - f1));
        glVertex2f(0 +   f2, 1  + (24 - f1));
        glVertex2f(1 +   f2, 1 + (24 -  f1));
        glVertex2f(0 +   f2, 1  + (24 - f1));
        glVertex2f(0 +   f2, 0  + (24 - f1));
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex2f(0 +   f2, 0.5  + (24 - f1));
        glVertex2f(0.5 + f2, 0.5  + (24 - f1));
        glEnd();
        ++i;
        space += 0.3;
        continue;
      }

      if ((name[i] == 'g') || (name[i] == 'G'))
      {
        float g1 =  where_down;
        float g2 =  where_right + float(i) + space;
        glBegin(GL_LINE_LOOP);
        glVertex2f(0 +   g2, 0  + (24 - g1));
        glVertex2f(0 +   g2, 1  + (24 - g1));
        glVertex2f(1 +   g2, 1 + (24 -  g1));
        glVertex2f(0 +   g2, 1  + (24 - g1));
        glVertex2f(0 +   g2, 0  + (24 - g1));
        glVertex2f(1 +   g2, 0 + (24 -  g1));
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex2f(1 +   g2,   0 + (24 -  g1));
        glVertex2f(1 +   g2,   0.5 + (24 -  g1));
        glVertex2f(0.6 +   g2, 0.5 + (24 -  g1));
        glVertex2f(0.6 +   g2, 0.2 + (24 -  g1));
        glVertex2f(0.6 +   g2, 0.5 + (24 -  g1));
        glVertex2f(1 +   g2,   0.5 + (24 -  g1));
        glVertex2f(1 +   g2,   0 + (24 -  g1));
        glEnd();
        ++i;
        space += 0.3;
        continue;
      }

      if ((name[i] == 'h') || (name[i] == 'H'))
      {
        float h1 =   where_down;
        float h2 =   where_right + float(i) + space;
        glBegin(GL_LINE_LOOP);
        glVertex2f(0 +   h2, 0  + (24 - h1));
        glVertex2f(0 +   h2, 1 +  (24 - h1));
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex2f(1 +   h2, 0  + (24 - h1));
        glVertex2f(1 +   h2, 1  + (24 - h1));
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex2f(0 +   h2, 0.5  + (24 - h1));
        glVertex2f(1 +   h2, 0.5  + (24 - h1));
        glEnd();
        ++i;
        space += 0.3;
        continue;
      }

      if ((name[i] == 'i') || (name[i] == 'I'))
      {
        float i1 =  where_down;
        float i2 =  where_right + float(i) + space;
        glBegin(GL_LINE_LOOP);
        glVertex2f(0.1 +   i2, 1  + (24 - i1));
        glVertex2f(0.9 +   i2, 1 +  (24 - i1));
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex2f(0.1 +   i2, 0  + (24 - i1));
        glVertex2f(0.9 +   i2, 0  + (24 - i1));
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex2f(0.5 +   i2, 1  + (24 - i1));
        glVertex2f(0.5 +   i2, 0  + (24 - i1));
        glEnd();
        ++i;
        space += 0.3;
        continue;
      }

      if ((name[i] == 'j') || (name[i] == 'J'))
      {
        float j1 =  where_down;
        float j2 =  where_right + float(i) + space;
        glBegin(GL_LINE_LOOP);
        glVertex2f(1 +   j2,   1  + (24 - j1));
        glVertex2f(1 +   j2,   0 +  (24 - j1));
        glVertex2f(0 +   j2,   0  + (24 - j1));
        glVertex2f(0 +   j2,   0.4  + (24 - j1));
        glVertex2f(0.4 +   j2, 0.4  + (24 - j1));
        glVertex2f(0 +   j2,   0.4  + (24 - j1));
        glVertex2f(0 +   j2,   0  + (24 - j1));
        glVertex2f(1 +   j2,   0 +  (24 - j1));
        glEnd();
        ++i;
        space += 0.3;
        continue;
      }

      if ((name[i] == 'k') || (name[i] == 'K'))
      {
        float k1 =  where_down;
        float k2 =  where_right + float(i) + space;
        glBegin(GL_LINE_LOOP);
        glVertex2f(0 +   k2, 0  + (24 - k1));
        glVertex2f(0 +   k2, 1 +  (24 - k1));
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex2f(0 +   k2, 0.5  + (24 - k1));
        glVertex2f(1 +   k2, 1  + (24 - k1));
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex2f(0 +   k2, 0.5  + (24 - k1));
        glVertex2f(1 +   k2, 0  + (24 - k1));
        glEnd();
        ++i;
        space += 0.3;
        continue;
      }

      if ((name[i] == 'l') || (name[i] == 'L'))
      {
        float l1 =  where_down;
        float l2 =  where_right + float(i) + space;
        glBegin(GL_LINE_LOOP);
        glVertex2f(0 +   l2, 0  + (24 - l1));
        glVertex2f(0 +   l2, 1 +  (24 - l1));
        glVertex2f(0 +   l2, 0  + (24 - l1));
        glVertex2f(1 +   l2, 0  + (24 - l1));
        glEnd();
        ++i;
        space += 0.3;
        continue;
      }

      if ((name[i] == 'm') || (name[i] == 'M'))
      {
        float m1 =  where_down;
        float m2 =  where_right + float(i) + space;
        glBegin(GL_LINE_LOOP);
        glVertex2f(0 +   m2, 0  + (24 - m1));
        glVertex2f(0 +   m2, 1 +  (24 - m1));
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex2f(1 +   m2, 0  + (24 - m1));
        glVertex2f(1 +   m2, 1  + (24 - m1));
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex2f(1 +   m2,   1  + (24 - m1));
        glVertex2f(0.5 +   m2, 0.7  + (24 - m1));
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex2f(0 +   m2,   1  + (24 - m1));
        glVertex2f(0.5 +   m2, 0.7  + (24 - m1));
        glEnd();
        ++i;
        space += 0.3;
        continue;
      }

      if ((name[i] == 'n') || (name[i] == 'N'))
      {
        float n1 =  where_down;
        float n2 =  where_right + float(i) + space;
        glBegin(GL_LINE_LOOP);
        glVertex2f(0 +   n2, 0  + (24 - n1));
        glVertex2f(0 +   n2, 1 +  (24 - n1));
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex2f(1 +   n2, 0  + (24 - n1));
        glVertex2f(1 +   n2, 1  + (24 - n1));
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex2f(0 +   n2, 1  + (24 - n1));
        glVertex2f(1 +   n2, 0  + (24 - n1));
        glEnd();
        ++i;
        space += 0.3;
        continue;
      }

      if ((name[i] == 'o') || (name[i] == 'o'))
      {
        float o1         =  where_down;
        float o2         =  where_right + float(i) + space;
        float xCenter    = 0.5 + o2;
        float yCenter    = 24.5 - o1;
        float rx         = 0.5;
        float ry         = 0.5;
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
        space += 0.3;
        continue;
      }

      if ((name[i] == 'p') || (name[i] == 'P'))
      {
        float p1 =  where_down;
        float p2 =  where_right + float(i) + space;
        glBegin(GL_LINE_LOOP);
        glVertex2f(0 +   p2, 0  + (24 - p1));
        glVertex2f(0 +   p2, 1 +  (24 - p1));
        glVertex2f(1 +   p2, 1  + (24 - p1));
        glVertex2f(1 +   p2, 0.5  + (24 - p1));
        glVertex2f(0 +   p2, 0.5  + (24 - p1));
        glVertex2f(0 +   p2, 0  + (24 - p1));
        glEnd();
        ++i;
        space += 0.3;
        continue;
      }

      if ((name[i] == 'q') || (name[i] == 'Q'))
      {
        float q1           = where_down;
        float q2           = where_right + float(i) + space;
        float q_xCenter    = 0.5 + q2;
        float q_yCenter    = 24.5 - q1;
        float q_rx         = 0.5;
        float q_ry         = 0.5;
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
        glVertex2f(1 +   q2,   0  + (24 - q1));
        glVertex2f(0.5 +   q2, 0.2  + (24 - q1));
        glEnd();
        ++i;
        space += 0.3;
        continue;
      }

      if ((name[i] == 'r') || (name[i] == 'r'))
      {
        float r1 = where_down;
        float r2 = where_right + float(i) + space;
        glBegin(GL_LINE_LOOP);
        glVertex2f(0 +   r2, 0  + (24 - r1));
        glVertex2f(0 +   r2, 1 +  (24 - r1));
        glVertex2f(1 +   r2, 1  + (24 - r1));
        glVertex2f(1 +   r2, 0.5  + (24 - r1));
        glVertex2f(0 +   r2, 0.5  + (24 - r1));
        glVertex2f(1 +   r2, 0  + (24 - r1));
        glVertex2f(0 +   r2, 0.5  + (24 - r1));
        glVertex2f(0 +   r2, 0  + (24 - r1));
        glEnd();
        ++i;
        space += 0.3;
        continue;
      }

      if ((name[i] == 's') || (name[i] == 'S'))
      {
        float s1 =  where_down;
        float s2 =  where_right + float(i) + space;
        glBegin(GL_LINE_LOOP);
        glVertex2f(0 +   s2, 0  + (24 -   s1));
        glVertex2f(1 +   s2, 0 +  (24 -   s1));
        glVertex2f(1 +   s2, 0.5  + (24 -   s1));
        glVertex2f(0 +   s2, 0.5  + (24 -   s1));
        glVertex2f(0 +   s2, 1  + (24 - s1));
        glVertex2f(1 +   s2, 1  + (24 - s1));
        glVertex2f(0 +   s2, 1  + (24 - s1));
        glVertex2f(0 +   s2, 0.5  + (24 -   s1));
        glVertex2f(1 +   s2, 0.5  + (24 -   s1));
        glVertex2f(1 +   s2, 0 +  (24 -   s1));
        glEnd();
        ++i;
        space += 0.3;
        continue;
      }

      if ((name[i] == 't') || (name[i] == 'T'))
      {
        float t1 =  where_down;
        float t2 =  where_right + float(i) + space;
        glBegin(GL_LINE_LOOP);
        glVertex2f(0 +   t2, 1  + (24 - t1));
        glVertex2f(1 +   t2, 1 +  (24 - t1));
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex2f(0.5 +   t2, 1  + (24 - t1));
        glVertex2f(0.5 +   t2, 0  + (24 - t1));
        glEnd();
        ++i;
        space += 0.3;
        continue;
      }

      if ((name[i] == 'u') || (name[i] == 'U'))
      {
        float u1 = where_down;
        float u2 = where_right + float(i) + space;
        glBegin(GL_LINE_LOOP);
        glVertex2f(0 +   u2, 0  + (24 - u1));
        glVertex2f(0 +   u2, 1 +  (24 - u1));
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex2f(1 +   u2, 0  + (24 - u1));
        glVertex2f(1 +   u2, 1  + (24 - u1));
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex2f(0 +   u2, 0  + (24 - u1));
        glVertex2f(1 +   u2, 0  + (24 - u1));
        glEnd();
        ++i;
        space += 0.3;
        continue;
      }

      if ((name[i] == 'v') || (name[i] == 'V'))
      {
        float v1 =  where_down;
        float v2 =  where_right + float(i) + space;
        glBegin(GL_LINE_LOOP);
        glVertex2f(0 +   v2, 1  + (24 - v1));
        glVertex2f(0.5 + v2, 0 +  (24 - v1));
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex2f(0.5 +   v2, 0  + (24 - v1));
        glVertex2f(1 +   v2,   1  + (24 - v1));
        glEnd();
        ++i;
        space += 0.3;
        continue;
      }

      if ((name[i] == 'w') || (name[i] == 'W'))
      {
        float w1 =  where_down;
        float w2 =  where_right + float(i) + space;
        glBegin(GL_LINE_LOOP);
        glVertex2f(0 +   w2,   1  + (24 - w1));
        glVertex2f(0.2 +   w2, 0 +  (24 - w1));
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex2f(0.2 +   w2, 0  + (24 - w1));
        glVertex2f(0.5 +   w2, 0.5  + (24 - w1));
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex2f(0.5 +   w2, 0.5  + (24 - w1));
        glVertex2f(0.8 +   w2, 0  + (24 - w1));
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex2f(0.8 +   w2, 0  + (24 - w1));
        glVertex2f(1 +   w2,   1  + (24 - w1));
        glEnd();
        ++i;
        space += 0.3;
        continue;
      }

      if ((name[i] == 'x') || (name[i] == 'X'))
      {
        float x1 =  where_down;
        float x2 =  where_right + float(i) + space;
        glBegin(GL_LINE_LOOP);
        glVertex2f(0 +   x2, 1  + (24 - x1));
        glVertex2f(1 + x2,   0 +  (24 - x1));
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex2f(0 +   x2, 0  + (24 - x1));
        glVertex2f(1 +   x2, 1  + (24 - x1));
        glEnd();
        ++i;
        space += 0.3;
        continue;
      }

      if ((name[i] == 'y') || (name[i] == 'Y'))
      {
        float y1 =  where_down;
        float y2 =  where_right + float(i) + space;
        glBegin(GL_LINE_LOOP);
        glVertex2f(0 +  y2,  1  + (24 - y1));
        glVertex2f(0.5 + y2, 0.5 +  (24 - y1));
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex2f(1 +  y2,  1  + (24 - y1));
        glVertex2f(0.5 + y2, 0.5 +  (24 - y1));
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex2f(0.5 +   y2, 0.5  + (24 - y1));
        glVertex2f(0.5 +   y2, 0  + (24 - y1));
        glEnd();
        ++i;
        space += 0.3;
        continue;
      }

      if ((name[i] == 'z') || (name[i] == 'Z'))
      {
        float z1 =  where_down;
        float z2 =  where_right + float(i) + space;
        glBegin(GL_LINE_LOOP);
        glVertex2f(0 +  z2, 1  + (24 - z1));
        glVertex2f(1 + z2,  1 +  (24 - z1));
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex2f(1 +   z2, 1  + (24 - z1));
        glVertex2f(0 +   z2, 0  + (24 - z1));
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex2f(0 +   z2, 0 + (24 - z1));
        glVertex2f(1 +   z2, 0  + (24 - z1));
        glEnd();
        ++i;
        space += 0.3;
        continue;
      }

      if  (name[i] == ' ')
      {
        ++i;
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
