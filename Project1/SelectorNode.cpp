#include "SelectorNode.hpp"

void SelectorNode::AddChild(std::shared_ptr<BTNode> child) {
    children.push_back(child);
}
NodeState SelectorNode::execute() {
    for (auto& child : children) {
        if (child->execute() == NodeState::SUCCESS) {
            return NodeState::SUCCESS;
        }
    }
    return NodeState::FAILURE;
}

std::vector<std::shared_ptr<BTNode>> SelectorNode::getChildren() { return children; }