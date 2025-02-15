#pragma once
#include "BTNode.hpp"
#include "Blackboard.hpp"


class ConditionNode : public BTNode {
private:
    Blackboard& blackboard;
    int key;
    int expectedValue;
public:
    ConditionNode(Blackboard& bb, const int& key, int value) : blackboard(bb), key(key), expectedValue(value) {}
    NodeState execute() override;
    int& getExpectedValue();
};