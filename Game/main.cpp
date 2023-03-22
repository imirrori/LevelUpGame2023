//dsd
#include "Game.h"
#include "Visualizer.h"
/*
    Dev. version
*/

int main(int argc, char **argv) // добавлены argc argv для работы openGL
{
    Game game;
    game.Run();
    glutInit(&argc, argv);  //возможно внести в часть класса?
    Visual::Visualizer vis;
    vis.make_window();
    return 0;
}
