#include "Visualizer.hpp"

namespace Visual {
void DisplayRender()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glFlush();
}

void Reshape(int, int)
{
  glOrtho(0, 640, 0, 480, 1, 0);
}

void Visualizer::make_window(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB);
  glutInitWindowSize(640, 480);
  glutCreateWindow("Wind");
  glutDisplayFunc(&DisplayRender);
  glutReshapeFunc(&Reshape);
}

void Visualizer::init(int argc, char **argv)
{
  make_window(argc, argv);
}

void Visualizer::mainloop()
{
  glutMainLoop();
}
}
