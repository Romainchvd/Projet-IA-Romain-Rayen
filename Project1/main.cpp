#include "Game.hpp"

int main() {
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Jeu SFML - IA Ennemis"); // Création de la fenetre de jeu
    Game game(window); //Objet game créé avec la window
    game.run(); //Exécution
    return 0;
}