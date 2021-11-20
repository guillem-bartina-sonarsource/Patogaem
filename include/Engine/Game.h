#ifndef GAME_HPP
#define GAME_HPP

#include <list>

#include "INonCopyable.h"
#include "Window.h"

class Game : private INonCopyable
{
    public:

    Game();
    ~Game();

    void launch(Window* window);
    void wait();

    private:

    std::list<Window*> windows;

};

#endif