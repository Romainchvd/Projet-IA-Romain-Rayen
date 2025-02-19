#include "Player.hpp"
#include <vector>
#include "BTEnemy.hpp"
#include "FSMEnemy.hpp"
#include "GOAPAgent.hpp"
using namespace std;
using namespace sf;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;


int main() {
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Jeu SFML - IA Ennemis");
    window.setFramerateLimit(60);

    Player player(200, 500);
    Grid grid;
    grid.loadFromFile("map.txt");
    Clock clock;
    FloatRect playerHitbox;
    BTEnemy btEnemy((float)75, (float)100, grid, player);
    FSMEnemy fsmEnemy((float)650, (float)100, grid, player);
    GOAPAgent goapEnemy(200, 400, player, grid);
    

    while (window.isOpen()) {
        
        
        Time dt = clock.restart();
        float deltaTime = dt.asSeconds();

        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            if(event.type == Event::KeyPressed && event.key.code == Keyboard::Enter)
                window.close();
        }

        player.update(deltaTime, grid);
        btEnemy.update(deltaTime, grid);
        fsmEnemy.update(deltaTime, grid);
        goapEnemy.PerformActions();

        window.clear();
        grid.draw(window);
        window.draw(player.shape);       
        window.draw(btEnemy.shape);
        window.draw(fsmEnemy.shape);
        window.draw(goapEnemy.enemy.shape);
        window.display();
    }
    return 0;
}