#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <functional>
#include <thread>

#include "INonCopyable.h"

#include "SFML/System/Clock.hpp"
#include "SFML/System/Time.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

class IScene;

class Window : private INonCopyable
{
    public:

    class Builder;
    class View;

    ~Window();

    void join();
    
    private:

    bool isFullscreen;
    sf::Vector2u size;
    float fullscreenXOffset;

    sf::RenderWindow window;

    IScene* scene;

    std::thread* thread;

    sf::Clock clock;

    Window(const Builder& builder);

    void init();
    void loop();

    void handleEvents();
    void update();
    void draw();

};

class Window::Builder
{
    public:

    Builder(IScene* scene);

    Builder& setSize(unsigned int width, unsigned int height);
    Builder& setFullscreen(unsigned int logicalWidth, unsigned int logicalHeight, bool alsoStyle = true);
    Builder& setTitle(const std::string& title);
    Builder& setStyle(sf::Uint32 style);

    Builder& enableMultiscene();

    Window* build();

    //Icon?

    private:

    IScene* scene;

    bool isFullscreen;
    sf::Vector2u size;
    std::string title;
    sf::Uint32 style;

    friend class Window;

};

class Window::View
{
    public:

    View(Window* window);
    ~View();

    sf::Vector2u getSize() const;
    bool isFullscreen() const;
    sf::Vector2u getScreenSize() const;
    sf::Vector2i getPosition() const;
    bool hasFocus() const;

    sf::Image capture() const;

    //setPosition, setSize, setTitle, setIcon, setVisible, requestFocus, setView, getView, map-world coords

    private:

    Window* window;

};

#endif