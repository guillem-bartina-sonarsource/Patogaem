#include "Engine/Game.h"

Game::Game() {}

Game::~Game() {}

void Game::launch(Window* window)
{
    windows.push_back(window);
}

void Game::wait()
{
    std::list<Window*>::iterator it = windows.begin();
    while(it != windows.end())
    {
        (*it)->join();
        it++;
    }
}