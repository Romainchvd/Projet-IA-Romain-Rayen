#include "FSMEnemy.hpp"

FSMEnemy::FSMEnemy(float x, float y, Grid& grid, Player& player) :Enemy(x, y), grid(grid), player(player) { shape.setFillColor(Color::Red);
shape.setPosition(x, y); position = shape.getPosition(); }

void FSMEnemy::patrol() {
    static int currentWaypoint = 0;
    static Vector2f waypoints[4] = { Vector2f(650, 100), Vector2f(400, 100), Vector2f(400, 200), Vector2f(650, 200)};
    Vector2f target = waypoints[currentWaypoint];
    Vector2f direction = target - position;
    float distance = sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance < 5.0f) {
        currentWaypoint = (currentWaypoint + 1) % 4;
    }
    else {
        direction /= distance;
        position += direction * 2.0f;
    }

    shape.setPosition(position);
}
void FSMEnemy::update(float deltaTime, Grid& grid) {
    checkDetection();
    runFSM(deltaTime);
}

void FSMEnemy::runFSM(float deltaTime)
{
        switch (currentState) {
        case PATROL:
            patrol();
            if (PlayerDetected == 1) currentState = CHASE;
            break;

        case CHASE:
            chase();
            if (PlayerDetected == 0) {
                lastPlayerPosition = player.shape.getPosition();
                
                currentState = SEARCH;
            }
            break;

        case SEARCH:
            search(deltaTime);
            break;
        }
}
void FSMEnemy::checkDetection()
{
    if (player.hitbox.intersects(shape.getGlobalBounds()))
    {
        PlayerDetected = 1;
    }
    else
        PlayerDetected = 0;
}
void FSMEnemy::chase()
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
void FSMEnemy::search(float deltaTime) {
    static float searchTimer = 0.0f;
    static Vector2f searchDirection;

    if (searchTimer == 0.0f) {
        searchDirection = Vector2f(rand() % 2 == 0 ? -1 : 1, rand() % 2 == 0 ? -1 : 1);
        searchDirection /= sqrt(searchDirection.x * searchDirection.x + searchDirection.y * searchDirection.y);
    }

    searchTimer += deltaTime;
    if (searchTimer < 10.0f) {
        position += searchDirection* 5.f * deltaTime;
    }
    else {
        searchTimer = 0.0f;
        currentState = PATROL;
    }

    float distance = sqrt((lastPlayerPosition.x - position.x) * (lastPlayerPosition.x - position.x) + (lastPlayerPosition.y - position.y) * (lastPlayerPosition.y - position.y));
    if (distance < player.detectionMargin) {
        searchTimer = 0.0f;
    }

    shape.setPosition(position);
    if (PlayerDetected == 1)
        currentState = CHASE;
    Vector2f newPosition = shape.getPosition();
    FloatRect newBounds(newPosition, shape.getSize());
    auto isWalkable = [&](float x, float y) {
        int gridX = static_cast<int>(x / CELL_SIZE);
        int gridY = static_cast<int>(y / CELL_SIZE);
        return gridX >= 0 && gridX < GRID_WIDTH && gridY >= 0 && gridY < GRID_HEIGHT && grid.getCell(gridX, gridY).walkable;
        };
    if (!(isWalkable(newBounds.left, newBounds.top) &&
        isWalkable(newBounds.left + newBounds.width - 1, newBounds.top) &&
        isWalkable(newBounds.left, newBounds.top + newBounds.height - 1) &&
        isWalkable(newBounds.left + newBounds.width - 1, newBounds.top + newBounds.height - 1))) {
        currentState = PATROL;
    }
}