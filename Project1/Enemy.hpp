#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Entity.hpp"
#include "Player.hpp"

class Enemy : public Entity {
public:
    static constexpr float SPEED = 100.0f;
    Enemy(float x, float y);
    void update(float deltaTime, Grid& grid) override;
    void chase(Player& player, Grid& grid);
};

#endif // ENEMY_HPP