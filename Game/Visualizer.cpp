#include "Visualizer.h"

namespace Visual
{
void DisplayRender()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

void Reshape(int, int)
{
    glOrtho (0,640, 0, 480, 1, 0);
}

void Visualizer::make_window()
{
    int argc = 0;  // это тоже магические числа получаются?
    char* argv[1];  // это тоже магические числа получаются?
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(640,480);
    glutCreateWindow("Wind");
    glutDisplayFunc(&DisplayRender);
    glutReshapeFunc(&Reshape);
}

void Visualizer::init()
{
    make_window();
}

void Visualizer::mainloop()
{
    glutMainLoop();
}

}
