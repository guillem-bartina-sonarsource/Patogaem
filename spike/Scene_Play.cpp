
#include "Scene_Play.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

#include "Engine/Resources.h"
#include "EntityCreator.hpp"
#include "PhysicEntity.hpp"
#include "TestPE.hpp"
#include "Duck.hpp"

bool EntityComp::operator()(const Entity* e1, const Entity* e2) const
{
    return (*e1 < *e2);
}

Scene_Play::Scene_Play(unsigned int levelnum) : IScene(), world(b2Vec2(0.f, 40.f))
{
    ID = 0;
    world.SetContactListener(&collisionHandler);

    background.setPosition(0, 0);
    background.setSize(sf::Vector2f(1000, 1000));

    duck = new Duck(this, sf::Vector2f(300, 900));
    static_cast<PhysicEntity*>(duck)->physicize(world);

    level.deserialize(levelnum);

    //IMGUI
    duckHBs = false;
    sceneHBs = false;
    currentEntity = 0;
}

Scene_Play::~Scene_Play()
{
    delete duck;

    for(EntityHolder::iterator it = entities.cbegin(); it != entities.cend(); it++)
    {
        delete *it;
    }

    //core.window->setView(core.window->getDefaultView());
}

void Scene_Play::init()
{
    view.setSize(sf::Vector2f(1000, 1000));
    view.setCenter(sf::Vector2f(CELLSIZE.x * NUMCELLS.x, CELLSIZE.y * NUMCELLS.y) * 0.5f);
    //core.window->setView(view);

    loadLevel(&level);
}

void Scene_Play::handleEvents(const sf::Event& event)
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
                case sf::Keyboard::P:
                {
                    sf::Vector2f pos = sf::Vector2f(sf::Mouse::getPosition(/**core.window*/)) - (view.getSize() * 0.5f) + (view.getCenter());
                    createEntity(getEntitybyCode(EntityCode(Entity_Code[currentEntity]), this, cellToPixels(sf::Vector2u(pos.x / CELLSIZE.x, pos.y / CELLSIZE.y))));
                }
                    break;
                default:
                    break;
            }
        }
            break;
        case sf::Event::MouseButtonPressed:
        {
        }
            break;
        default:
            break;
    }

    if(static_cast<Duck*>(duck)->isAlive()) static_cast<Duck*>(duck)->handleEvents(event);
}

void Scene_Play::update(const sf::Time& deltatime)
{
    //TEMPORAL
    sf::Vector2f duckPosToView = duck->getPosition() - view.getCenter();
    sf::Vector2f movingBounds = sf::Vector2f(1000, 1000) * 0.2f;;

    if(duckPosToView.x > movingBounds.x) view.move(sf::Vector2f(duckPosToView.x - movingBounds.x, 0.f));
    else if(duckPosToView.x < -movingBounds.x) view.move(sf::Vector2f(duckPosToView.x + movingBounds.x, 0.f));
    if(duckPosToView.y > movingBounds.y) view.move(sf::Vector2f(0.f, duckPosToView.y - movingBounds.y));
    else if(duckPosToView.y < -movingBounds.y) view.move(sf::Vector2f(0.f, duckPosToView.y + movingBounds.y));

    //--------------

    //core.window->setView(view);
    background.setPosition(view.getCenter() - view.getSize() / 2.f);

    world.Step(deltatime.asSeconds(), 8, 8);

    //Update entities
    duck->update(deltatime);

    for(EntityHolder::iterator it = entities.begin(); it != entities.end(); it++)
    {
        (*it)->update(deltatime);
    }

    while(not toDestroy.empty())
    {
        Entity* e = toDestroy.front();
        delete e;
        entities.erase(e);
        toDestroy.pop();
    }
    
    //IMGUI
    //imgui();
}

void Scene_Play::draw(Renderer renderer) const
{
    renderer(background);

    for(EntityHolder::const_iterator it = entities.cbegin(); it != entities.cend(); it++)
    {
        renderer(**it);
        if(sceneHBs and isTarjet(*it, IS_PHYSICENTITY))
        {
            std::vector<sf::RectangleShape> hbs;
            static_cast<PhysicEntity*>(*it)->getHBs(hbs);
            for(unsigned int i = 0; i < hbs.size(); i++) renderer(hbs[i]);

            /* MILLORAR */
            sf::Text text;
            text.setFont(*Resources::getInstance()->Font("fonts/font.ttf"));
            text.setCharacterSize(18);
            text.setString(std::to_string((*it)->getID()));
            text.setPosition((*it)->getPosition() - sf::Vector2f(20, 0));
            renderer(text);
        }
    }

    renderer(*duck);

    if(duckHBs)
    {
        std::vector<sf::RectangleShape> hbs;
        static_cast<PhysicEntity*>(duck)->getHBs(hbs);
        for(unsigned int i = 0; i < hbs.size(); i++) renderer(hbs[i]);
    }
}

void Scene_Play::pause() {}

void Scene_Play::resume() {}

sf::Vector2f Scene_Play::cellToPixels(sf::Vector2u cell) const
{
    assert(cell.x <= NUMCELLS.x and cell.y <= NUMCELLS.y);
    return sf::Vector2f(cell.x * CELLSIZE.x, cell.y * CELLSIZE.y) + (sf::Vector2f(CELLSIZE) * 0.5f);
}

unsigned int Scene_Play::getNextID()
{
    ID++;
    return ID;
}

EntityHolder::iterator Scene_Play::createEntity(Entity* entity)
{
    std::pair<EntityHolder::iterator, bool> it = entities.insert(entity);
    if(isTarjet(*it.first, IS_PHYSICENTITY)) static_cast<PhysicEntity*>(*it.first)->physicize(world);

    return it.first;
}

void Scene_Play::destroyEntity(Entity* entity)
{
    toDestroy.push(entity);
}

void Scene_Play::addEntity(Entity* entity)
{
    entities.insert(entity);
}

void Scene_Play::deleteEntity(Entity* entity)
{
    entities.erase(entity);
}

const Level& Scene_Play::getLevel() const
{
    return level;
}

void Scene_Play::loadLevel(const Level* level)
{
    entities.clear();

    background.setTexture(Resources::getInstance()->Texture(level->getBackground()));

    //CHANGE IT TO MAP OF SETS TRANSVERSAL!!!
    for(int i = 0; i < NUMCELLS.x; i++)
    {
        for(int j = 0; j < NUMCELLS.y; j++)
        {
            if(not level->isEmpty(Coord(i, j)))
            {
                for(auto it = level->get(Coord(i, j)).cbegin(); it != level->get(Coord(i, j)).cend(); it++)
                {
                    createEntity(getEntitybyCode(EntityCode(*it), this, cellToPixels(sf::Vector2u(i, j))));
                }
            }
        }
    }
}

void Scene_Play::imgui()
{
    if(DEBUG_MENU_ENABLE)
    {
        bool open = true;
        ImGui::SetNextWindowSize(ImVec2(200, 400));
        ImGui::Begin("DEBUG", &open);

        ImGui::Separator();
        ImGui::Text("State: ");
        ImGui::SameLine();
        ImGui::Text(MovementState_String[static_cast<Duck*>(duck)->getState()].c_str());
        ImGui::Text("Hd: ");
        ImGui::SameLine();
        ImGui::Text(std::to_string(static_cast<Duck*>(duck)->getHeadings()).c_str());
        ImGui::Text("Gr: ");
        ImGui::SameLine();
        ImGui::Text(std::to_string(static_cast<Duck*>(duck)->getGroundings()).c_str());
        ImGui::Separator();

        if(ImGui::CollapsingHeader("HBs"))
        {
            ImGui::Checkbox("Duck HBs", &duckHBs);
            ImGui::Checkbox("Scene HBs", &sceneHBs);
        }

        if(ImGui::CollapsingHeader("Entities"))
        {
            ImGui::Text("Cast with 'P': ");
            ImGui::ListBox("Entities", &currentEntity, Entity_String, IM_ARRAYSIZE(Entity_String), 10);
        }

        ImGui::End();
    }
}
