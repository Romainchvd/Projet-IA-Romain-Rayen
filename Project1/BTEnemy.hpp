#pragma once
#include "Enemy.hpp"
#include "ActionNode.hpp"
#include "ConditionNode.hpp"
#include "SelectorNode.hpp"
#include "SequenceNode.hpp"

class BTEnemy : public Enemy {
public:
	shared_ptr<SelectorNode> root = make_shared<SelectorNode>();
	shared_ptr<SequenceNode> sequence = make_shared<SequenceNode>();
	Blackboard blackboard;
	Grid& grid;
	Player& player;
	int PlayerDetected = 0;
	void update(float deltaTime, Grid& grid) override;
	void chase(Player& player, Grid& grid);
	void patroll() override;
	void checkDetection();
	BTEnemy(float posX, float posY, Grid& grid, Player& player);

};