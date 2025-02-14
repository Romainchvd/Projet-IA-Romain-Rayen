#pragma once
#include "BTNode.hpp"

class ActionNode : public BTNode {
private:
    std::string actionName;
public:
    ActionNode(std::string name) : actionName(name) {}
    NodeState execute() override;
};