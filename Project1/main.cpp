#include "Player.hpp"
#include "Enemy.hpp"
#include <vector>
#include "ActionNode.hpp"
#include "ConditionNode.hpp"
#include "SelectorNode.hpp"
#include "SequenceNode.hpp"
using namespace std;
using namespace sf;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int detectionMargin = 100;

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Jeu SFML - IA Ennemis");
    window.setFramerateLimit(60);

    Player player(200, 400);
    std::vector<Enemy> enemies = { Enemy(100, 100), Enemy(700, 100) };
    enemies[0].shape.setFillColor(Color::Green);
    Grid grid;
    grid.loadFromFile("map.txt");

    sf::Clock clock;

    Blackboard blackboard;
    int PlayerDetected = 0;
    

    auto root = std::make_shared<SelectorNode>();
    auto sequence = std::make_shared<SequenceNode>();
    FloatRect playerHitbox;
    
    
    sequence->AddChild(std::make_shared<ConditionNode>(blackboard, PlayerDetected, 1));
    sequence->AddChild(std::make_shared<ActionNode>("Suivre"));
    

    root->AddChild(sequence);
    root->AddChild(std::make_shared<ActionNode>("Patrouiller"));

    while (window.isOpen()) {
        blackboard.SetValue(PlayerDetected, 1);
        if(PlayerDetected == 1)
            enemies[0].chase(player, grid);
        playerHitbox.left = player.shape.getGlobalBounds().left - detectionMargin;
        playerHitbox.top = player.shape.getGlobalBounds().top - detectionMargin;
        playerHitbox.height = player.shape.getGlobalBounds().height + detectionMargin*2;
        playerHitbox.width = player.shape.getGlobalBounds().width + detectionMargin*2;

        if (playerHitbox.intersects(enemies[0].shape.getGlobalBounds()))
        {
            PlayerDetected = 1;
        }
        else
            PlayerDetected = 0;
      if(auto* sequenceNode = dynamic_cast<SequenceNode*>(root->getChildren()[0].get()))
      {
          if (auto* conditionNode = dynamic_cast<ConditionNode*>(sequenceNode->getChildren()[0].get()))
          {
              int& expectedValue = conditionNode->getExpectedValue();
              expectedValue = PlayerDetected;
       }
    }
        
        
       
        
        

        root->execute();
        sf::Time dt = clock.restart();
        float deltaTime = dt.asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        player.update(deltaTime, grid);
        for (auto& enemy : enemies) {
            enemy.update(deltaTime, grid);
        }

        window.clear();
        grid.draw(window);
        window.draw(player.shape);
        for (const auto& enemy : enemies)
            window.draw(enemy.shape);
        window.display();
    }
    return 0;
}