#pragma once
#include "BTNode.hpp"
using namespace std;

class SequenceNode : public BTNode {
private:
    vector<shared_ptr<BTNode>> children;
public:
    void AddChild(shared_ptr<BTNode> child);
    NodeState execute() override;
    vector<shared_ptr<BTNode>> getChildren();
};