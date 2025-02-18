#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entity.hpp"
const int detectionMargin = 100;

class Player : public Entity {
public:
    FloatRect hitbox;
    static constexpr float SPEED = 200.0f;
    Player(float x, float y);
    void update(float deltaTime, Grid& grid) override;

};

#endif // PLAYER_HPP