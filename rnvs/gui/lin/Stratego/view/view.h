#ifndef VIEW_H
#define VIEW_H
#include "model/game.h"
#include "keyboardAndStringConvert/keyboard.hpp"
/**
* @brief The View class includes all displays
*/
class View{
private:
    Game * model;

public:
    /**
    * @brief View the constructor of the class
    * @param model includes the trade classes
    */
    View(Game * model);
    View() = default;
    /**
    * @brief displayWelcome Displays information to the player such as player,
    game title and game version
    */
    void displayWelcome();
    /**
    * @brief displayGame Displays the battlefield where the 2 players play
    */
    void displayGame();
    /**
    * @brief displayAttacker Allows you to display a summary of an attack to the current player
    * @param soldier The soldier who was attacked
    * @param pos The position of the soldier in a board
    */
    void displayAttacker(std::optional<GameElement> soldier, Position pos);
    /**
    * @brief displayWinner Displays the winner of the game
    */
    void displayWinner();

};


#endif // VIEW_H
