#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "model/game.h"
#include "view/view.h"
#include <vector>
/**
* @brief The Controller class is the intermediary between the view and the model
*/
class Controller {
private:
    Game * model;
    View * view;
    std::optional<GameElement> saveSoldier;
    Position savePos;
    /**
    * @brief makeAction allows to make an action on the game, moove or attack
    */
    void makeAction();
    /**
    * @brief initialiseGame allows to create a game with the parameters chosen by the player and manages the placement according to the chosen mode
    */
    void initialiseGame();
    void initialiseGameFile();
    void initialiseGamePlacement(PLAYER currentPlayer);
    /**
    * @brief fillVectorSoldier allows to fill a vector with all the pieces of the game for the
    * @param soldier the vector that will
    * @param color a color of PLAYER enumeration
    */
    void fillVectorSoldier(std::vector<GameElement> & soldier, PLAYER color);
    std::vector<GameElement> soldierBlue;
    std::vector<GameElement> soldierRed;
    /**
    * @brief askPositionPlacement asks for the placement position to place its element
    * @return a new position requested by the current player
    */
    Position askPositionPlacement();
    /**
    * @brief askPositionToGo asks for the position where the current player wants to go
    * @return a new position requested by the current playerr
    */
    Position askPositionToGo();
    /**
    * @brief askPosition asks for the position of the soldier the current player wants to play with
    * @return a new position requested by the current player
    */
    Position askPosition();
    /**
    * @brief askDirection asks for a direction where the current player wants to move his soldier
    * @return a direction that the player has chosen
    */
    DIRECTION askDirection();
    /**
    * @brief askInitializeGame asks by what means does he want to fill his battlefield
    * @return a string with the mode that he want to fill his battlefield
    */
    std::string askInitializeGame();
    /**
    * @brief askDistance asks for the distance to be covered to reach the desired position
    * @return an integer representing the distance
    */
    int askDistance();
    /**
    * @brief askLevel asks for the level of play that the players want
    * @return the level of the game chosen
    */
    LEVEL askLevel();
    /**
    * @brief directionTs allows to transforms a direction into a position
    * @param dir a direction that the player has chosen
    * @return a position which is a transformation from direction to position
    */
    Position directionTs(DIRECTION dir);
    /**
    * @brief conditionPosition Allows you to check all the rules for a position such as being on the board,and position toGo is
    *  not being a bomb or a flag. Do not move towards the water, towards an allied soldier
    * @param pos p the position where is the soldier that you want to move
    * @param toGo the position where we want to move our soldier
    * @return a boolean if all conditions are met
    */
    bool conditionPosition(Position pos, Position toGo);

public:
    /**
    * @brief Controller Constructor of the class controller
    * @param model the model of architecture MVC
    * @param view the view of MVC architecture
    */
    Controller(Game * model,View * view);
    /**
    * @brief play allows to manage a game from the beginning to the end by managing the state change
    */
    void play();

};

#endif // CONTROLLER_H
