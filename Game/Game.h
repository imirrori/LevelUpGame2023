#ifndef GAME_H
#define GAME_H

#include "Visualizer.h"
#include <memory>

class Game
    : public Visual::Visualizer
{
private:
    std::shared_ptr<Visual::Visualizer>_viz;
public:
    void Init();
    void Run();

    Game();
};

#endif // GAME_H
