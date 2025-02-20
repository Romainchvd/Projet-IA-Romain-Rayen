#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entity.hpp"
class Enemy;


class Player : public Entity {
public:
    FloatRect hitbox;
    FloatRect endOfDetectionArea;
    Clock detectionClock;
    Time detectionCooldown = seconds(0.4);
    static constexpr float SPEED = 200.0f;
    Player(float x, float y);
    void update(float deltaTime, Grid& grid) override;
    int detectionMargin = 100;
    int endOfDetectionMargin = 125;
    bool onColision = false;

};

#endif // PLAYER_HPP