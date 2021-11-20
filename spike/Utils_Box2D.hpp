#ifndef UTILS__BOX2D_HPP
#define UTILS__BOX2D_HPP

#include <utility>

#include "SFML/Graphics/Transformable.hpp"
#include "box2d/box2d.h"

inline static sf::Vector2f toVector2f(b2Vec2 from)
{
    return sf::Vector2f(from.x, from.y);
}

inline static b2Vec2 tob2Vec2(sf::Vector2f from)
{
    return b2Vec2(from.x, from.y);
}

const static float conversion = 64.f;

inline static float pixelize(float value)
{
    return value*conversion;
}

inline static sf::Vector2f pixelize(sf::Vector2f value)
{
    return value*conversion;
}

inline static b2Vec2 pixelize(b2Vec2 value)
{
    return b2Vec2(value.x*conversion, value.y*conversion);
}

inline static float metrize(float value)
{
    return value/conversion;
}

inline static sf::Vector2f metrize(sf::Vector2f value)
{
    return value/conversion;
}

inline static b2Vec2 metrize(b2Vec2 value)
{
    return b2Vec2(value.x/conversion, value.y/conversion);
}

inline static float anglize(float value)
{
    return value * (180/b2_pi);
}

inline static float radize(float value)
{
    return value * (b2_pi/180);
}

static void move(b2Body* from, sf::Transformable& to)
{
    to.setPosition(pixelize(toVector2f(from->GetPosition())));
    to.setRotation(anglize(from->GetAngle()));
}

static b2PolygonShape* createRectangle(b2Vec2 size, b2Vec2 offset = b2Vec2_zero, float angle = 0.f)
{
    b2PolygonShape* rectangle = new b2PolygonShape();
    rectangle->SetAsBox(metrize(size.x/2), metrize(size.y/2), metrize(offset), angle); //Because of it's from the center

    return rectangle;
}

static b2EdgeShape createEdge(b2Vec2 v1, b2Vec2 v2)
{
    b2EdgeShape edge;
    edge.SetTwoSided(metrize(v1), metrize(v2));

    return edge;
}

static b2Body* createBody(b2World& world, b2Vec2 position, b2BodyType type, b2Shape* shape, float density, float friction, float restitution)
{
    b2Body* body;

    b2BodyDef bodyDef;
    bodyDef.position = metrize(position);
    bodyDef.type = type;

    body = world.CreateBody(&bodyDef);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = shape;
    fixtureDef.density = density;
    fixtureDef.friction = friction;
    fixtureDef.restitution = restitution;

    body->CreateFixture(&fixtureDef);

    return body;
}

#endif