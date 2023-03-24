#ifndef VISUALIZER_H
#define VISUALIZER_H

#include <GL/freeglut.h>
#include <GL/glu.h>

namespace Visual
{
class Visualizer
{
public:
    void make_window();
    void init();
    void mainloop();
};
}

#endif // VISUALIZER_H
