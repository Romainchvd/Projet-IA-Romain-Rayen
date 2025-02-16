#include "SequenceNode.hpp"


void SequenceNode::AddChild(std::shared_ptr<BTNode> child) {
    children.push_back(child);
}
NodeState SequenceNode::execute()  {
    for (auto& child : children) {
        if (child->execute() == NodeState::FAILURE) {
            return NodeState::FAILURE;
        }
    }
    return NodeState::SUCCESS;
}

std::vector<std::shared_ptr<BTNode>> SequenceNode::getChildren() { return children; }