#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Player.hpp"
#include "Enemy.hpp"
#include "Grid.hpp"
class GOAPEnemy : public Enemy{
public:
    Player& player;
    Grid& grid;
    bool PlayerDetected = false;
    void patrol() override;
    void runAway();
    void checkPlayerDetected();
    void checkColision();
    Clock respawnClock;
    Time respawnDuration = seconds(5);
    GOAPEnemy(float x, float y, Player& player, Grid& grid);
};