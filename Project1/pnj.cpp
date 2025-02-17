#include "pnj.h"
using namespace std;
using namespace sf;
PNJ::PNJ(Vector2f startPos, float radiusDetect, float radiusCircle) {
    circle.setRadius(radiusCircle);
    circle.setPosition(startPos);
    circle.setFillColor(Color::Red);
    position = startPos;
    detectionRadius = radiusDetect;
    currentState = PATROL;
}

bool PNJ::detectPlayer(Vector2f playerPos) {

    float distance = sqrt(pow(playerPos.x - position.x, 2) + pow(playerPos.y - position.y, 2));
    return (distance < detectionRadius);
}

void PNJ::patrol() {
    static int currentWaypoint = 0;
    static Vector2f waypoints[4] = { Vector2f(100, 300), Vector2f(500, 100), Vector2f(100, 300), Vector2f(500, 300) };
    Vector2f target = waypoints[currentWaypoint];
    Vector2f direction = target - position;
    float distance = sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance < 5.0f) {
        currentWaypoint = (currentWaypoint + 1) % 4;
    }
    else {
        direction /= distance;
        position += direction * 0.2f;
    }
    circle.setPosition(position);
}

void PNJ::chase(Vector2f playerPos) {
    Vector2f direction = playerPos - position;
    float distance = sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance > 0) {
        direction /= distance;
        position += direction * 0.2f;
    }

    circle.setPosition(position);
}

void PNJ::search(Vector2f lastPlayerPos, float deltaTime) {
    static float searchTimer = 0.0f;
    static Vector2f searchDirection;

    if (searchTimer == 0.0f) {
        searchDirection = Vector2f(rand() % 2 == 0 ? -1 : 1, rand() % 2 == 0 ? -1 : 1);
        searchDirection /= sqrt(searchDirection.x * searchDirection.x + searchDirection.y * searchDirection.y);
    }

    searchTimer += deltaTime;
    if (searchTimer < 10.0f) {
        position += searchDirection * 5.f * deltaTime;
    }
    else {
        searchTimer = 0.0f;
        currentState = PATROL;
    }

    float distance = sqrt((lastPlayerPos.x - position.x) * (lastPlayerPos.x - position.x) + (lastPlayerPos.y - position.y) * (lastPlayerPos.y - position.y));
    if (distance < detectionRadius) {
        searchTimer = 0.0f;
    }

    circle.setPosition(position);
}

void PNJ::update(Vector2f playerPos, float deltaTime) {
    switch (currentState) {
    case PATROL:
        patrol();
        if (detectPlayer(playerPos)) currentState = CHASE;
        break;

    case CHASE:
        chase(playerPos);
        if (!detectPlayer(playerPos)) {
            lastPlayerPosition = playerPos;
            currentState = SEARCH;
        }
        break;

    case SEARCH:
        search(lastPlayerPosition, deltaTime);
        break;
    }
}