#pragma once

#include "Entity.hpp"
#include "Player.hpp"


class Enemy : public Entity {
public:
    static constexpr float SPEED = 100.0f;
    Vector2f position;
    virtual void patrol() = 0;
    void update(float deltaTime, Grid& grid) override;
    Enemy(float x, float y);
};
