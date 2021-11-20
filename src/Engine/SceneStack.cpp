#include "Engine/SceneStack.h"

#include <iostream>

SceneStack::SceneStack(IScene* scene) : IScene()
{
    scenes.push(scene);
}

SceneStack::~SceneStack()
{
    while(not scenes.empty())
    {
        delete scenes.top();
        scenes.pop();
        if(not scenes.empty())
        {
            scenes.top()->resume();
        }
    }
}

void SceneStack::init(Window::View* window)
{
    this->window = window;
    scenes.top()->init(window);
}

void SceneStack::handleEvents(const sf::Event& event)
{
    if(not scenes.empty())
    {
        scenes.top()->handleEvents(event);
    }
}

void SceneStack::update(const sf::Time& deltatime)
{
    IScene* scene;
    bool replace;
    while(not scenes.empty() and scenes.top()->pollRequest(scene, replace))
    {
        if(scene)
        {
            if(replace)
            {
                delete scenes.top();
                scenes.pop();
            }
            else
            {
                scenes.top()->pause();
            }
            scenes.push(scene);
            scenes.top()->init(window);
        }
        else
        {
            scenes.pop();
            if(scenes.empty())
            {
                closeScene();
            }
            else
            {
                scenes.top()->resume();
            }
        }
    }
    if(not scenes.empty())
    {
        scenes.top()->update(deltatime);
    }
}

void SceneStack::draw(Renderer render) const
{
    if(not scenes.empty())
    {
        scenes.top()->draw(render);
    }
}
