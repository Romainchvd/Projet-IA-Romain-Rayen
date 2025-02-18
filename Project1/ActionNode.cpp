#include "ActionNode.hpp"
#include "BTEnemy.hpp"
NodeState ActionNode::execute() {
    if (actionName == "Suivre")
    {
        enemy.chase(player, grid);
    }
    else
    {
        enemy.patroll();
    }
    return NodeState::SUCCESS;
}