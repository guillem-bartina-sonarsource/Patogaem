
#include "SceneMenu.h"

#include "SFML/Graphics/RectangleShape.hpp"
#include "Engine/Resources.h"

#include "SceneTest.h"

#include "imgui/imgui.h"

const std::string SceneMenu::texts[NUM_OPTIONS] = {"PLAY", "EDITOR", "EXIT"};

SceneMenu::SceneMenu(int x)
: IScene()
{
    this->x = x;
}

SceneMenu::~SceneMenu() {}

void SceneMenu::init(Window::View* window)
{
    title.setFont(*Resources::getInstance()->Font("fonts/font.ttf"));
    title.setString("PATOGAEM :P (" + std::to_string(x) + ")");
    title.setCharacterSize(36);
    title.setFillColor(sf::Color::Yellow);
    title.setPosition(86, 100);

    for(int i = 0; i < NUM_OPTIONS; i++)
    {
        options[i].setFont(*Resources::getInstance()->Font("fonts/font.ttf"));
        options[i].setString(texts[i]);
        options[i].setCharacterSize(20);
        options[i].setFillColor(sf::Color::White);
        options[i].setPosition(160, (300+i*100));
    }

    currentOption = 0;

    updateRequest = true;
}

void SceneMenu::handleEvents(const sf::Event& event)
{
    switch(event.type)
    {
        case sf::Event::KeyPressed:
        {
            switch(event.key.code)
            {
                case sf::Keyboard::Escape:
                {
                    closeScene();
                }
                    break;
                case sf::Keyboard::Down:
                {
                    if(currentOption < NUM_OPTIONS-1) currentOption++;

                    updateRequest = true;
                }
                    break;
                case sf::Keyboard::Up:
                {
                    if(currentOption > 0) currentOption--;
                
                    updateRequest = true;
                }
                    break;
                case sf::Keyboard::Return:
                {
                    switch(currentOption)
                    {
                        case 0:
                            changeScene(new SceneTest(), false);
                            break;
                        case 1:
                            changeScene(new SceneMenu(x+1), false);
                            //changeScene(new Scene_Editor(), false);
                            break;
                        case 2:
                            closeScene();
                            break;
                        default:
                            break;
                    }
                }
                    break;
                default:
                    break;
            }
        }
            break;
        default:
            break;
    }

    if(updateRequest)
    {
        for(int i = 0; i < NUM_OPTIONS; i++)
        {
            if(i == currentOption) options[i].setFillColor(sf::Color::Green);
            else options[i].setFillColor(sf::Color::White);
        }
        updateRequest = false;
    }
}

void SceneMenu::update(const sf::Time& deltatime) {}

void SceneMenu::draw(Renderer renderer) const
{
    sf::RectangleShape rs;
    rs.setSize(sf::Vector2f(1000, 800));
    rs.setPosition(0.f, 0.f);
    rs.setFillColor(sf::Color::Red);
    rs.setOutlineThickness(-2.f);
    rs.setOutlineColor(sf::Color::Blue);

    renderer(rs);

    renderer(title);
    
    for(int i = 0; i < NUM_OPTIONS; i++) renderer(options[i]);

    ImGui::Begin("HELLO");
    ImGui::Button("Pretty button");
    ImGui::End();
}
