#include "ActionNode.hpp"
#include "BTEnemy.hpp"
NodeState ActionNode::execute() {
    if (actionName == "Suivre")
    {
        enemy.chase();
        
    }
    else
    {
        enemy.patrol();
    }
    return NodeState::SUCCESS;
}