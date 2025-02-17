#include "SelectorNode.hpp"
using namespace std;
void SelectorNode::AddChild(shared_ptr<BTNode> child) {
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

vector<shared_ptr<BTNode>> SelectorNode::getChildren() { return children; }