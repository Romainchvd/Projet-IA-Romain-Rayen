#include "ConditionNode.hpp"

NodeState ConditionNode::execute() {
    return (blackboard.GetValue(key) == expectedValue) ? NodeState::SUCCESS : NodeState::FAILURE;
}

//int& ConditionNode::getExpectedValue() { return expectedValue; }