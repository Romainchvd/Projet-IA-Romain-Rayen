#include "BTEnemy.hpp"

BTEnemy::BTEnemy(float posX, float posY, Grid& grid, Player& player) : Enemy(posX, posY), grid(grid), player(player) {
	shape.setPosition(posX, posY); shape.setFillColor(Color::Green); 
	sequence->AddChild(make_shared<ConditionNode>(blackboard, PlayerDetected, 1));
	sequence->AddChild(make_shared<ActionNode>("Suivre", *this, grid, player));
	root->AddChild(sequence);
	root->AddChild(make_shared<ActionNode>("Patrouiller", *this, grid, player));
	position = shape.getPosition();
}

void BTEnemy::patroll()
{
	static int currentWaypoint = 0;
	static Vector2f waypoints[2] = { Vector2f(75, 100), Vector2f(75, 300) };
	Vector2f target = waypoints[currentWaypoint];
	Vector2f direction = target - position;
	float distance = sqrt(direction.x * direction.x + direction.y * direction.y);

	if (distance < 5.0f) {
		currentWaypoint = (currentWaypoint + 1) % 2;
	}
	else {
		direction /= distance;
		position += direction * 2.0f;
	}

	shape.setPosition(position);
}

void BTEnemy::checkDetection()
{
	if (player.hitbox.intersects(shape.getGlobalBounds()))
	{
		PlayerDetected = 1;
	}
	else
		PlayerDetected = 0;
}

void BTEnemy::chase(Player& player, Grid& grid)
{


	Vector2f newPosition = shape.getPosition();
	FloatRect newBounds(newPosition, shape.getSize());
	auto isWalkable = [&](float x, float y) {
		int gridX = static_cast<int>(x / CELL_SIZE);
		int gridY = static_cast<int>(y / CELL_SIZE);
		return gridX >= 0 && gridX < GRID_WIDTH && gridY >= 0 && gridY < GRID_HEIGHT && grid.getCell(gridX, gridY).walkable;
		};
	if (isWalkable(newBounds.left, newBounds.top) &&
		isWalkable(newBounds.left + newBounds.width - 1, newBounds.top) &&
		isWalkable(newBounds.left, newBounds.top + newBounds.height - 1) &&
		isWalkable(newBounds.left + newBounds.width - 1, newBounds.top + newBounds.height - 1)) {

		Vector2f direction = player.shape.getPosition() - position;
		float distance = sqrt(direction.x * direction.x + direction.y * direction.y);

		if (distance > 0) {
			direction /= distance;
			position += direction * 2.0f;
		}
		shape.setPosition(position);
	}

}

void BTEnemy::update(float deltaTime, Grid& grid) { checkDetection(); blackboard.SetValue(PlayerDetected, 1);

if (auto* sequenceNode = dynamic_cast<SequenceNode*>(root->getChildren()[0].get()))
{
	if (auto* conditionNode = dynamic_cast<ConditionNode*>(sequenceNode->getChildren()[0].get()))
	{
		int& expectedValue = conditionNode->getExpectedValue();
		expectedValue = PlayerDetected;
	}
}
root->execute();
}