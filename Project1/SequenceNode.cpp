#include "SequenceNode.hpp"
using namespace std;

void SequenceNode::AddChild(shared_ptr<BTNode> child) {
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

vector<shared_ptr<BTNode>> SequenceNode::getChildren() { return children; }