#include "Game.hpp"

int main() {
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Jeu SFML - IA Ennemis"); // Cr�ation de la fenetre de jeu
    Game game(window); //Objet game cr�� avec la window
    game.run(); //Ex�cution
    return 0;
}