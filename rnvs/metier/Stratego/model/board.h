#ifndef BOARD_H
#define BOARD_H
#include "gameElement.h"
#include "position.h"
#include "enum.h"           // rnvs : include / déclaration anticipée
#include <vector>
#include <string>
#include <array>
/**
* @brief The Board class contains the battlefield and all possible actions on the board
*/
class Board
{
  private:
    std::array<std::array<GameElement, 10>, 10> battleField;
    std::vector<Position> water {Position(4, 2), Position(5, 2), Position(4, 3), Position(5, 3), Position(4, 6), Position(5, 6), Position(4, 7), Position(5, 7)};
    /**
    * @brief fillArray allows to fill the battlefield
    * @param power an integer representing the power of the game element that will be placed
    * @param player color of PLAYER enumeration representing the player who will place
    * @param row an integer representing row of the board
    * @param col an integer representing column of the board
    */
    void fillArray(int power, PLAYER player, int row, int col);
    /**
    * @brief mirrorVector allows to apply the mirror effect on a vector
    * @param s the vector that will be affected
    */
    void mirrorVector(std::vector<std::string> & s);
    /**
    * @brief attack allows to flatten an attack between 2 soldiers (bomb included), respecting the rules, and delete the weakest soldier
    * @param p position of the running player's soldier
    * @param toAttack position of the enemy soldier to attack
    * @return a game element that is the winning soldier
    */
    GameElement attack(Position p, Position toAttack);
    /**
    * @brief reveal Allows to reveal a soldier at a given position by modifying his visible attribute
    * @param p the position of the soldier who will be revealed
    */
    void reveal(Position p);
    /**
    * @brief unReveal Allows to unreveal a soldier at a given position by modifying his visible attribute
    * @param p the position of the soldier who will be unrevealed
    */
    void unReveal(Position p);
  public:
    Board();
    /**
    * @brief initializeBattleField Allows you to initialize the battlefield with a file containing the disposition of the troops
    * @param s a file containing the layout of the troops
    * @param player player the current player
    */
    void initializeBattleField(std::vector<std::string> s, PLAYER player);
    /**
    * @brief initializeBattleField Allows to initialize the field element by element according to each player
    * @param p the position where the game element will be placed
    * @param player the current player
    * @param s element of the game that will be placed
    */
    void initializeBattleField(Position p, PLAYER player, GameElement s);
    /**
    * @brief canBePlaceStart check if it is possible to place at the beginning of the game respecting the water, the opposite camp and the battlefield
    * @param pos p the position where you want to choose a soldier
    * @param player the current player
    * @return a boolean if it is possible or not to place
    */
    bool canBePlaceStart(Position p, PLAYER player);
    /**
    * @brief canBePlace check if it is possible to place an element in the battlefield according to the rules of the game
    * @param p the position where you want to move an element
    * @return a boolean if it is possible or not to place
    */
    bool canBePlace(const Position & p);
    /**
    * @brief moveEclaireur allows you to move or attack with ECLAIREUR according to the ECLAIREUR own rules
    * @param p the position where is the ECLAIREUR that you want to move
    * @param toGo the position where the ECLAIREYR will be go
    * @param dir the direction in which the ECLAIREUR will move
    * @param distance an integer representing the travel distance
    * @return a boolean if it is possible to move the ECLAIREUR
    */
    bool moveEclaireur(Position & p, Position & toGo, Position dir,
                       int distance);
    /**
    * @brief removeFromBattle allows you to remove a soldier (including bomb and flag) from the battlefield
    * @param p the position of the soldier who will be removed
    */
    void removeFromBattle(const Position & p);
    /**
    * @brief endGame check if it is the end of the game as a flag has been captured or there are no more soldiers to fight
    * @param soldier who will be checked if it is a flag
    * @return a boolean if it is the of the game
    */
    int endGame();
    /**
    * @brief move allows you to move or attack with a soldier according to the game rules
    * @param p the position where is the soldier that you want to move
    * @param dir the direction in which the soldier will move
    * @param distance an integer representing the distance to be covered
    * @return an integer 1 when the game is lost with the capture of a flag or an integer 2 when the game is lost because there are no soldiers
    * on the battlefield ready to fight,or simply 0 when the game is not finished
    */
    std::optional<GameElement> move(Position p, DIRECTION dir,
                                    int distance = 1);
    /**
    * @brief fillVectorSoldier allows to fill the vector of soldiers (bomb and flags included)
    * @param soldier the vector of the current player
    * @param color a color of PLAYER enumeration who is the current player
    */
    void fillVectorSoldier(std::vector<GameElement> & soldier,
                           PLAYER color);
    /**
    * @brief canBeTake allows to check if the soldier to use belongs to the current player
    * @param pos p the position where you want to choose a soldier
    * @param player the current player
    * @return a boolean if it is possible or not to place
    */
    bool canBeTake(const Position & pos, PLAYER player);
    /**
    * @brief getSoldier allows to get an element of the game at a certain position
    * @param p position where we get the game element
    * @return a gameElement at position
    */
    GameElement & getSoldier(const Position &
                             pos); // je pense qu'ici on va devoir choisir entre celui la
    /**
    * @brief isFull check if all the pieces have been placed and modify the state to move
    * @return a boolean if all the pieces have been placed at the begenning the game
    */
    bool isFull();
};
inline std::ostream & operator<<(std::ostream & os, Board & bd)
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            // if(bd.getSoldier(Position(i,j)).getVisible() == true){
            if (bd.getSoldier(Position(i, j)).getColor() == BLUE)
            {
                os << "B" << std::setw(3) << bd.getSoldier(Position(i, j));
            }
            else if (bd.getSoldier(Position(i, j)).getColor() == RED)
            {
                os << "R" << std::setw(3) << bd.getSoldier(Position(i, j));
            }
            else if (bd.getSoldier(Position(i, j)).getDecor() == "W")
            {
                os << std::setw(3) << bd.getSoldier(Position(i, j));
            }
            else
            {
                os << std::setw(3) << bd.getSoldier(Position(i, j));
            }
        }
        os << std::endl;
    }
    return os;
}

#endif // BOARD_H
