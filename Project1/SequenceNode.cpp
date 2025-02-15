#include "SequenceNode.hpp"


void SequenceNode::AddChild(std::unique_ptr<BTNode> child) {
    children.push_back(std::move(child));
}
NodeState SequenceNode::execute()  {
    for (auto& child : children) {
        if (child->execute() == NodeState::FAILURE) {
            return NodeState::FAILURE;
        }
    }
    return NodeState::SUCCESS;
}

//std::vector<std::unique_ptr<BTNode>> SequenceNode::getChildren() { return children; }