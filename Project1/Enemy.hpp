#pragma once
#include "Entity.hpp"
#include "Player.hpp"
#include <iostream>


class Enemy : public Entity {
public:
    static constexpr float SPEED = 100.0f;
    Vector2f position;
    virtual void patrol() = 0;
    void update(float deltaTime) override;
    Enemy(float x, float y);
    bool doDraw = true;
    void toggleDraw();
    bool isAlive = true;
};
