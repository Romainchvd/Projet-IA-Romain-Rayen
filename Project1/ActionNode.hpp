#pragma once
#include "BTNode.hpp"
#include "Enemy.hpp"
#include "Grid.hpp"

using namespace std;
class ActionNode : public BTNode {
private:
    string actionName;
    
public:
    ActionNode(string name) : actionName(name) {}
    NodeState execute() override;
};