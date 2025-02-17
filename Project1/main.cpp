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
const int detectionMargin = 150;

int main() {
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Jeu SFML - IA Ennemis");
    window.setFramerateLimit(60);

    Player player(200, 400);
    vector<Enemy> enemies = { Enemy(75, 100), Enemy(700, 100) };
    enemies[0].shape.setFillColor(Color::Green);
    Grid grid;
    grid.loadFromFile("map.txt");

    Clock clock;

    Blackboard blackboard;
    int PlayerDetected = 0;
    

    auto root = make_shared<SelectorNode>();
    auto sequence = make_shared<SequenceNode>();
    FloatRect playerHitbox;
    
    
    sequence->AddChild(make_shared<ConditionNode>(blackboard, PlayerDetected, 1));
    sequence->AddChild(make_shared<ActionNode>("Suivre", enemies[0], grid, player));
    

    root->AddChild(sequence);
    root->AddChild(make_shared<ActionNode>("Patrouiller", enemies[0], grid, player));

    while (window.isOpen()) {
        
        blackboard.SetValue(PlayerDetected, 1);
        //if (PlayerDetected == 1)
        //{
        //    enemies[0].chase(player, grid);
        //}
        //else
        //    enemies[0].patroll();

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