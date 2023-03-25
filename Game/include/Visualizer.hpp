#ifndef VISUALIZER_HPP
#define VISUALIZER_HPP

#include <GL/freeglut.h>
#include <GL/glu.h>

namespace Visual
{
class Visualizer
{
public:
    void make_window(int argc, char** argv);
    void init(int argc, char** argv);
    void mainloop();
};
}

#endif // VISUALIZER_HPP
