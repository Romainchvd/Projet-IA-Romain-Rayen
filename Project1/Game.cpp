#include "Game.hpp"

Game::Game(RenderWindow& window) : player(200, 500, grid), btEnemy(75, 100, grid, player), fsmEnemy(650, 100, grid, player), goapEnemy(200, 400, player, grid), window(window) {

    grid.loadFromFile("map.txt");
    window.setFramerateLimit(60);
    //Tous les ennemis, le joueur et la grille sont directement mis dans game. Les ennemis ont des références sur le player et la grille.
}

void Game::run() { //Run concentre toutes les méthodes
    while(isRunning)
    {
        while(window.isOpen())
        {
            input();
            update();
            draw();
        }
    }
}

void Game::input() { //Gestion des entrées utilisateurs

    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed)
        {
            window.close();
            isRunning = false;
        }
        if (event.type == Event::KeyPressed)
        {
            if (event.key.code == Keyboard::Enter)
            {
                window.close();
                isRunning = false;
            }
            if (event.key.code == Keyboard::G)
                goapEnemy.enemy.toggleDraw(); //Toggle draw est une méthode qui permet d'activer ou désactiver un ennemi. Les touches correspondent au différents algos.
            if (event.key.code == Keyboard::F)
                fsmEnemy.toggleDraw();
            if (event.key.code == Keyboard::B)
                btEnemy.toggleDraw();
        }
    }
}

void Game::update() {
    Time dt = clock.restart();
    float deltaTime = dt.asSeconds();

    if (player.shape.getGlobalBounds().intersects(btEnemy.shape.getGlobalBounds()) ||
        player.shape.getGlobalBounds().intersects(fsmEnemy.shape.getGlobalBounds()) ||
        player.shape.getGlobalBounds().intersects(goapEnemy.enemy.shape.getGlobalBounds()))
    {
        player.onColision = true;                        //Cette condition permet de vérifier si le joueur entre en contact avec un ennemi pour éviter les conflits lors du changement de couleur (checkColision dans les .cpp d'ennemis)
    }
    else
        player.onColision = false; 

    player.update(deltaTime);
    if (btEnemy.isAlive)
        btEnemy.update(deltaTime);
    if (fsmEnemy.isAlive)
        fsmEnemy.update(deltaTime);
    if (goapEnemy.enemy.isAlive)
        goapEnemy.PerformActions();
    //Les attributs isAlive sont gérés via le toggle
}

void Game::draw() {
    window.clear();
    grid.draw(window);
    window.draw(player.shape);
    if (btEnemy.doDraw)
        window.draw(btEnemy.shape);
    if (fsmEnemy.doDraw)
        window.draw(fsmEnemy.shape);
    if (goapEnemy.enemy.doDraw)
        window.draw(goapEnemy.enemy.shape);
    //doDraw géré de la même manière
    window.display();
}