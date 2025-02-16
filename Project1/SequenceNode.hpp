#pragma once
#include "BTNode.hpp"


class SequenceNode : public BTNode {
private:
    std::vector<std::shared_ptr<BTNode>> children;
public:
    void AddChild(std::shared_ptr<BTNode> child);
    NodeState execute() override;
    std::vector<std::shared_ptr<BTNode>> getChildren();
};