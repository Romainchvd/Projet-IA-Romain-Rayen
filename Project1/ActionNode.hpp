#pragma once
#include "BTNode.hpp"
#include "Enemy.hpp"
#include "Grid.hpp"

using namespace std;
class ActionNode : public BTNode {
private:
    string actionName;
    Player& player;
    Enemy& enemy;
    Grid& grid;
public:
    ActionNode(string name, Enemy& enemy, Grid& grid, Player& player) : actionName(name), enemy(enemy), grid(grid), player(player) {}
    NodeState execute() override;
};