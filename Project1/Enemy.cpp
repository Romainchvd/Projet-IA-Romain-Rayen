#include "Enemy.hpp"
#include <cmath>
using namespace sf;
Enemy::Enemy(float x, float y) : Entity(x, y, sf::Color::Red) { position = shape.getPosition(); }

void Enemy::update(float deltaTime, Grid& grid) {

}
void Enemy::chase(Player& player, Grid& grid)
{

	
	Vector2f movement(0.f, 0.f);
			Vector2f newPosition = shape.getPosition() + movement;
			FloatRect newBounds(newPosition, shape.getSize());
			auto isWalkable = [&](float x, float y) {
				int gridX = static_cast<int>(x / CELL_SIZE);
				int gridY = static_cast<int>(y / CELL_SIZE);
				return gridX >= 0 && gridX < GRID_WIDTH && gridY >= 0 && gridY < GRID_HEIGHT && grid.getCell(gridX, gridY).walkable;
				};
			shape.setPosition(position);
			if (isWalkable(newBounds.left, newBounds.top) &&
				isWalkable(newBounds.left + newBounds.width - 1, newBounds.top) &&
				isWalkable(newBounds.left, newBounds.top + newBounds.height - 1) &&
				isWalkable(newBounds.left + newBounds.width - 1, newBounds.top + newBounds.height - 1)) {
				
				sf::Vector2f direction = player.shape.getPosition() - position;
				float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

				if (distance > 0) {
					direction /= distance;
					position += direction * 2.0f;
				}
				shape.setPosition(position);
			}

}

void Enemy::patroll() {

		static int currentWaypoint = 0;
		static Vector2f waypoints[2] = {Vector2f(75, 100), Vector2f(75, 300) };
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

void Enemy::resetPos() {
	
	Vector2f target = Vector2f(100,100);
	Vector2f direction = target - position;
	float distance = sqrt(direction.x * direction.x + direction.y * direction.y);

	
		direction /= distance;
		position += direction * 2.0f;

	shape.setPosition(position);
}