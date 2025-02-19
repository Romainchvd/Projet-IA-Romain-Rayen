#pragma once
#include "GOAPEnemy.hpp"
#include "Action.hpp"
#include "Enemy.hpp"
#include "GOAPPlanner.hpp"
class GOAPAgent {
public:
    void PerformActions();
    GOAPAgent(float x, float y, Player& player, Grid& grid);
    GOAPEnemy enemy;
    GOAPPlanner planner;
};