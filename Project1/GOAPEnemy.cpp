#include "GOAPEnemy.hpp"

void GOAPEnemy::patrol() {
	static int currentWaypoint = 0;
	static Vector2f waypoints[2] = { Vector2f(200, 400), Vector2f(600, 400) };
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

GOAPEnemy::GOAPEnemy(float x, float y, Player& player, Grid& grid) : Enemy(x, y), player(player), grid(grid) { shape.setFillColor(Color::Magenta); }

void GOAPEnemy::checkPlayerDetected() {
	if (player.hitbox.intersects(shape.getGlobalBounds()) && !PlayerDetected && player.detectionClock.getElapsedTime().asSeconds() > player.detectionCooldown.asSeconds())
	{
		PlayerDetected = true;
		player.detectionClock.restart();
	}
	else if (PlayerDetected && player.endOfDetectionArea.intersects(shape.getGlobalBounds()) && !player.hitbox.intersects(shape.getGlobalBounds()))
	{
		PlayerDetected = false;
		
	}
}
void GOAPEnemy::checkColision() {
	if (player.shape.getGlobalBounds().intersects(shape.getGlobalBounds()))
	{
		shape.setFillColor(Color::White);
	}
	else
		shape.setFillColor(Color::Magenta);
}

void GOAPEnemy::runAway() {
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
			position -= direction * 2.0f;
		}
		shape.setPosition(position);
	}
}