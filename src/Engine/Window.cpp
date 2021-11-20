#include "Engine/Window.h"

#include "Engine/SceneStack.h"

#include "SFML/Window/Window.hpp"
#include "SFML/Window/Context.hpp"
#include "SFML/Window/Event.hpp"

#include <iostream>

Window::Window(const Builder& builder)
{
    isFullscreen = builder.isFullscreen;
    size = builder.size;
    scene = builder.scene;
    window.create(isFullscreen ? sf::VideoMode::getFullscreenModes()[0] : sf::VideoMode(size.x, size.y), builder.title, builder.style);
    window.setFramerateLimit(60); //THIS
    window.setActive(false);
    thread = new std::thread(&Window::init, this);
}

Window::~Window()
{
    delete thread;
    delete scene;
}

void Window::join()
{
    thread->join();
}

void Window::init()
{
    window.setActive(true);
    if(isFullscreen)
    {
        float ratio = float(size.x)/float(size.y);
        float fullscreenRatio = float(window.getSize().x)/float(window.getSize().y);
        float ratiosRatio = ratio/fullscreenRatio;
        sf::View view(sf::FloatRect(0.f, 0.f, float(size.x), float(size.y)));
        view.setViewport(sf::FloatRect((1.f-ratiosRatio)/2.f, 0.f, ratiosRatio, 1.f));
        window.setView(view);
        fullscreenXOffset = ((1.f-ratiosRatio)/2.f) * window.getSize().x;
    }
    scene->init(new Window::View(this));
    clock.restart();
    loop();
}

void Window::loop()
{
    IScene* scene;
    bool replace;
    while(window.isOpen())
    {
        handleEvents();
        update();
        draw();
        if(this->scene->pollRequest(scene, replace) and scene == nullptr)
        {
            window.close();
        }
    }
}

void Window::handleEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if(isFullscreen)
        {
            switch(event.type)
            {
                case sf::Event::MouseButtonPressed:
                case sf::Event::MouseButtonReleased:
                    event.mouseButton.x -= fullscreenXOffset;
                    break;
                case sf::Event::MouseMoved:
                    event.mouseMove.x -= fullscreenXOffset;
                    break;
                default:
                    break;
            }
        }
        scene->handleEvents(event);
    }
}

void Window::update()
{
    sf::Time deltatime = clock.restart();
    scene->update(deltatime);
}

void Window::draw()
{
    window.clear(sf::Color::Black);
    scene->draw([&](const sf::Drawable& drawable){ window.draw(drawable); });
    // std::bind(static_cast<void(sf::RenderWindow::*)(const sf::Drawable&, const sf::RenderStates&)>(&sf::RenderWindow::draw), &window, std::placeholders::_1, sf::RenderStates::Default)
    window.display();
}


Window::Builder::Builder(IScene* scene)
{
    isFullscreen = false;
    size = sf::Vector2u(800, 600);
    title = "";
    style = sf::Style::Close;
    this->scene = scene;
}

Window::Builder& Window::Builder::setSize(unsigned int width, unsigned int height)
{
    isFullscreen = false;
    size = sf::Vector2u(width, height);
    return *this;
}

Window::Builder& Window::Builder::setFullscreen(unsigned int logicalWidth, unsigned int logicalHeight, bool alsoStyle)
{
    isFullscreen = true;
    size = sf::Vector2u(logicalWidth, logicalHeight);
    if(alsoStyle)
    {
        style = sf::Style::Fullscreen;
    }
    return *this;
}

Window::Builder& Window::Builder::setTitle(const std::string& title)
{
    this->title = title;
    return *this;
}

Window::Builder& Window::Builder::setStyle(sf::Uint32 style)
{
    this->style = style;
    return *this;
}

Window::Builder& Window::Builder::enableMultiscene()
{
    scene = new SceneStack(scene);
    return *this;
}

Window* Window::Builder::build()
{
    return new Window(*this);
}


Window::View::View(Window* window)
{
    this->window = window;
}

Window::View::~View() {}

sf::Vector2u Window::View::getSize() const
{
    return window->size;
}

bool Window::View::isFullscreen() const
{
    return window->isFullscreen;
}

sf::Vector2u Window::View::getScreenSize() const
{
    return window->window.getSize();
}

sf::Vector2i Window::View::getPosition() const
{
    return window->window.getPosition();
}

bool Window::View::hasFocus() const
{
    return window->window.hasFocus();
}

sf::Image Window::View::capture() const
{
    return window->window.capture();
}

