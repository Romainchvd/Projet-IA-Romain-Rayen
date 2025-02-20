#include "Player.hpp"
#include <vector>
#include "BTEnemy.hpp"
#include "FSMEnemy.hpp"
#include "GOAPAgent.hpp"
using namespace std;
using namespace sf;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

bool doDrawBT = true;
bool doDrawFSM = true;
bool doDrawGOAP = true;

void toggle(bool& boolean)
{
    if (boolean)
        boolean = false;
    else
        boolean = true;
}

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
            if (event.type == Event::KeyPressed)
            {
                if(event.key.code == Keyboard::Enter)
                window.close();
                if (event.key.code == Keyboard::G)
                    toggle(doDrawGOAP);
                if (event.key.code == Keyboard::F)
                    toggle(doDrawFSM);
                if (event.key.code == Keyboard::B)
                    toggle(doDrawBT);
            }
        }
        if (player.shape.getGlobalBounds().intersects(btEnemy.shape.getGlobalBounds()) ||
            player.shape.getGlobalBounds().intersects(fsmEnemy.shape.getGlobalBounds()) ||
            player.shape.getGlobalBounds().intersects(goapEnemy.enemy.shape.getGlobalBounds()))
        {
            player.onColision = true;
        }
        else
            player.onColision = false;

        player.update(deltaTime, grid);
        if(doDrawBT)
        btEnemy.update(deltaTime, grid);
        if(doDrawFSM)
        fsmEnemy.update(deltaTime, grid);
        if(doDrawGOAP)
        goapEnemy.PerformActions();

        window.clear();
        grid.draw(window);
        window.draw(player.shape);
        if(doDrawBT)
        window.draw(btEnemy.shape);
        if(doDrawFSM)
        window.draw(fsmEnemy.shape);
        if(doDrawGOAP)
        window.draw(goapEnemy.enemy.shape);
        window.display();
    }
    return 0;
}