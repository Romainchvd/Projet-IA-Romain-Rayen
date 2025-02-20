#include "BTEnemy.hpp"

BTEnemy::BTEnemy(float posX, float posY, Grid& grid, Player& player) : Enemy(posX, posY), grid(grid), player(player) {
	shape.setPosition(posX, posY); shape.setFillColor(Color::Green); 
	sequence->AddChild(make_shared<ConditionNode>(blackboard, PlayerDetected, 1));
	sequence->AddChild(make_shared<ActionNode>("Suivre", *this, grid, player));
	root->AddChild(sequence);
	root->AddChild(make_shared<ActionNode>("Patrouiller", *this, grid, player));
	position = shape.getPosition();
	//L'arbre est créé dans le constructeur de l'objet
}

void BTEnemy::patrol()
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

		shape.setPosition(position);
		respawnClock.restart();
	}
	else
	{
		
		doDraw = false;
		cout << "CRASH!!!!!" << endl;
		if (respawnClock.getElapsedTime().asSeconds() > respawnDuration.asSeconds())
		{
			doDraw = true;
			position = waypoints[currentWaypoint];
			shape.setPosition(position);
		}
		//Seul l'ennemi géré par le behaviorTree peut se crash. Dans le cas du FSM, l'ennemi stope la recherche en cas de crash et le GOAP se coince s'il fuit. En cas de patrouille
		//pour les deux derniers, ils traversent les murs, le programme n'étant pas réalisé avec A* (trois algos). Tenter de bloquer la patrouille provoque un blocage permanent de l'ennemi,
		//d'où le choix de le garder ainsi.
	}
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

void BTEnemy::checkColision() {
	if (player.shape.getGlobalBounds().intersects(shape.getGlobalBounds()))
	{
		player.shape.setFillColor(Color::Cyan);
		
	}
	else if (!player.onColision)
		player.shape.setFillColor(Color::Blue);
	
}

void BTEnemy::chase()
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

void BTEnemy::update(float deltaTime) {
	checkDetection();
	checkColision();
	blackboard.SetValue(PlayerDetected, 1);
	

if (auto* sequenceNode = dynamic_cast<SequenceNode*>(root->getChildren()[0].get()))
{
	if (auto* conditionNode = dynamic_cast<ConditionNode*>(sequenceNode->getChildren()[0].get()))
	{
		int& expectedValue = conditionNode->getExpectedValue();
		expectedValue = PlayerDetected;
	}
}
//La fonction précédente met à jour l'accès à l'Attaque/Patrouille en fonction de si le joueur est détecté. La première condition empêche le programme de planter en tombant sur un pointeur
//indéfini (d'où l'avertissement sur visual studio)
root->execute();
}