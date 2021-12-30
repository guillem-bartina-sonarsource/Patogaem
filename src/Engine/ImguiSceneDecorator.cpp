#include "Engine/ImguiSceneDecorator.h"

#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

#include <iostream>

ImguiSceneDecorator::ImguiSceneDecorator(IScene* scene)
: scene(scene),
window(nullptr),
mousePosition(sf::Vector2i())
{}

ImguiSceneDecorator::~ImguiSceneDecorator()
{
    delete scene;
    if(this->window)
    {
        ImGui::SFML::Shutdown(this->window->getWindowId());
    }
}

void ImguiSceneDecorator::init(Window::View* window)
{
    if(this->window)
    {
        ImGui::SFML::Shutdown(this->window->getWindowId());
    }
    this->window = window;
    renderTexture.create(window->getSize().x, window->getSize().y);
    rectangle.setSize(sf::Vector2f(window->getSize()));
    rectangle.setTextureRect(sf::IntRect(0, window->getSize().y, window->getSize().x, -window->getSize().y));
    rectangle.setTexture(&renderTexture.getTexture());
    ImGui::SFML::Init(window->getWindowId(), window->hasFocus(), sf::Vector2f(window->getSize()));
    scene->init(window);
}

void ImguiSceneDecorator::handleEvents(const sf::Event& event)
{
    if(event.type == sf::Event::MouseMoved)
    {
        mousePosition = sf::Vector2i(event.mouseMove.x, event.mouseMove.y);
    }

    if(this->window)
    {
        ImGui::SFML::ProcessEvent(window->getWindowId(), event);
    }

    ImGuiIO& io = ImGui::GetIO();
    bool ignore = false;
    if(io.WantCaptureMouse)
    {
        ignore = ignore
                 or (event.type == sf::Event::MouseButtonPressed) 
                 or (event.type == sf::Event::MouseButtonReleased)
                 or (event.type == sf::Event::MouseMoved)
                 or (event.type == sf::Event::MouseWheelScrolled);
    }
    if(io.WantCaptureKeyboard)
    {
        ignore = ignore
                 or (event.type == sf::Event::TextEntered) 
                 or (event.type == sf::Event::KeyPressed)
                 or (event.type == sf::Event::KeyReleased);
    }
    if(not ignore)
    {
        scene->handleEvents(event);
    }
}

void ImguiSceneDecorator::update(const sf::Time& deltatime)
{
    if(this->window)
    {
        ImGui::SFML::Update(window->getWindowId(), mousePosition, sf::Vector2f(window->getSize()), deltatime);
    }

    scene->update(deltatime);

    IScene* scene;
    bool replace;
    if(this->scene->pollRequest(scene, replace))
    {
        if(scene)
        {
            changeScene(scene, replace);
        }
        else
        {
            closeScene();
        }
    }
}

void ImguiSceneDecorator::draw(Renderer renderer) const
{
    scene->draw(renderer);

    if(this->window)
    {
        renderTexture.clear(sf::Color::Transparent);
        ImGui::SFML::Render(renderTexture);
        renderer(rectangle);
    }
}

void ImguiSceneDecorator::pause() 
{
    scene->pause();
    ImGui::SFML::Shutdown(this->window->getWindowId());
}

void ImguiSceneDecorator::resume()
{
    ImGui::SFML::Init(window->getWindowId(), window->hasFocus(), sf::Vector2f(window->getSize()));
    scene->resume();
}
