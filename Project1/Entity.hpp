#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>
#include "Grid.hpp"

class Entity {
public:
    RectangleShape shape;
    Vector2f velocity;
    

    Entity(float x, float y, Color color);
    virtual void update(float deltaTime) = 0;
};

#endif // ENTITY_HPP