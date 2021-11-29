#ifndef ISCENE_H
#define ISCENE_H

#include "INonCopyable.h"
#include "Common.h"
#include "Window.h"

#include "SFML/System/Time.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Graphics/Drawable.hpp"

class IScene : private INonCopyable
{
    public:

    IScene();
    virtual ~IScene();

    virtual void init(Window::View* window) = 0;
    virtual void handleEvents(const sf::Event& event) = 0;
    virtual void update(const sf::Time& deltatime) = 0;
    virtual void draw(Renderer render) const = 0;
    virtual void pause();
    virtual void resume();

    bool pollRequest(IScene*& scene, bool& replace);

    protected:

    void changeScene(IScene* scene, bool replace = false);
    void closeScene();

    private:

    bool request;
    IScene* scene;
    bool replace;

};



#endif