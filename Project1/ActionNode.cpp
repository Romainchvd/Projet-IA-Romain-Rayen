#include "ActionNode.hpp"

NodeState ActionNode::execute() {
    if (actionName == "Suivre")
    {
        cout << "Action : " << actionName << endl;
    }
    else
    {
        cout << "Action: " << actionName << endl;
    }
    return NodeState::SUCCESS;
}