#pragma once
#include "BTNode.hpp"
#include "Player.hpp"
#include "Grid.hpp"
class BTEnemy;
using namespace std;
class ActionNode : public BTNode {
private:
    string actionName;
    Player& player;
    BTEnemy& enemy;
    Grid& grid;
public:
    ActionNode(string name, BTEnemy& enemy, Grid& grid, Player& player) : actionName(name), enemy(enemy), grid(grid), player(player) {}
    NodeState execute() override;
};