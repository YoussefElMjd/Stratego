#ifndef GAME_H
#define GAME_H
// #include "board.h"       // rnvs : include / déclaration anticipée

#include "enum.h"           // rnvs : include / déclaration anticipée
#include <optional>         // rnvs : include / déclaration anticipée
#include <vector>           // rnvs : include / déclaration anticipée
#include <string>           // rnvs : include / déclaration anticipée

class Board;                // rnvs : include / déclaration anticipée
class GameElement;          // rnvs : include / déclaration anticipée
class Position;             // rnvs : include / déclaration anticipée
/**
* @brief The Game class gathers all the elements of the Stratego game already coded and defines the players, the game mechanism

*/
class Game
{
  private:
    Board * board;
    STATUS state;
    PLAYER currentPlayer;
    LEVEL gameLevel;
    std::optional<GameElement *> oldSoldierRED;
    std::optional<GameElement *> oldSoldierBLUE;
    std::vector<std::string> movementBlue;
    std::vector<std::string> movementRed;
    /**
    * @brief reveal Allows to reveal a soldier at a given position by modifying his visible attribute
    * @param p the position of the soldier who will be revealed
    */
    void reveal(const Position & p);
    /**
    * @brief unReveal Allows to unreveal a soldier at a given position by modifying his visible attribute
    * @param p the position of the soldier who will be unrevealed
    */
    void unReveal(const Position & p);
    /**
    * @brief checkCanMakeMove Verify if it is possible to move respecting the rules of return
    * @return a boolean if it is possible or not
    */
    bool checkCanMakeMove(std::vector<std::string> &);
    /**
    * @brief fillMovementList allows to fill the vector movement if it is below 8 moves and verifies
    * if it is at 8 that the player is allowed to perform this move
    * @param canMakeMove the boolean that is modified to know if it is possible to make the movement
    * @param toGo the position to be added in the vector movement according to the current player
    */
    void fillMovementList(bool & canMakeMove, Position toGo);
    /**
    * @brief makeMove allows you to perform a moove in the battlefield by recovering the former soldier
    * @param saveSoldier the new soldier to save
    * @param p position where we get the game element(soldier)
    * @param direction a direction from DIRECTION enumeration
    * @param d a position who are a direction
    * @param distance an integer that is supposed to be 1 if it is a soldier other than ECLAIREUR that gives the distance to travel
    */
    void makeMove(std::optional<GameElement> & saveSoldier, Position p,
                  Position direction, DIRECTION d, int distance);
    /**
    * @brief clearMovementList allows to clear the vector for each player if the current soldier has been changed
    * @param p p position where we get the game element(soldier)
    */
    void clearMovementList(const Position p);
  public:
    /**
    * @brief Game Constructor of the class game
    * @param boardcontains the battlefield and all possible actions on the board
    * @param level a level from LEVEL enumeration
    */
    Game(Board & board, LEVEL level = DEBUTANT);

    Game() = default;
    /**
    * @brief initializeBattelField Allows you to initialize the battlefield with a file containing the disposition of the troops
    * @param file a file containing the layout of the troops
    */
    void initializeBattelField(const std::vector<std::string> & file);
    /**
    * @brief initializeBattleField Allows to initialize the field element by element according to each player
    * @param p the position where the game element will be placed
    * @param player the player who owns the game element
    * @param s element of the game that will be placed
    */
    void initializeBattleField(const Position & p, PLAYER player,
                               const GameElement & s);
    /**
    * @brief canBePlace check if it is possible to place an element in the battlefield according to the rules of the game
    * @param p the position where you want to move an element
    * @return a boolean if it is possible or not to place
    */
    bool canBePlace(const Position & p);
    /**
    * @brief canBePlaceStart check if it is possible to place at the beginning of the game respecting the water, the opposite camp and the battlefield
    * @param p the position where you want to place an element
    * @param player the current player
    * @return a boolean if it is possible or not to place
    */
    bool canBePlaceStart(const Position & p, PLAYER player);
    /**
    * @brief canBeTake allows to check if the soldier to use belongs to the current player
    * @param pos p the position where you want to choose a soldier
    * @param player the current player
    * @return a boolean if it is possible or not to place
    */
    bool canBeTake(const Position & pos, PLAYER player);
    /**
    * @brief move allows you to place a soldier according to the rules of the game if the square is empty or
    * directly attack an enemy soldier close to a square of the current player's soldier
    * @param p the position where you want to choose a soldier
    * @param d direction of the DIRECTION enumeration
    * @param distance agrument provided at 1
    * @return
    */
    //    std::optional<GameElement> move(Position & p, DIRECTION & d,
    //                                    int distance = 1);    // rnvs : comm
    std::optional<GameElement> move(const Position & p, DIRECTION & d,
                                    int distance = 1);  // rnvs : ajout
    /**
    * @brief nextPlayer Allows you to change the current player
    */
    void nextPlayer();
    /**
    * @brief endGame check if it is the end of the game as a flag has been captured or there are no more soldiers to fight
    * @param soldier who will be checked if it is a flag
    * @return a boolean if it is the of the game
    */
    int endGame();
    /**
    * @brief getWinnerPlayer allows to give the winner of the game
    * @return a color of PLAYER enumeration
    */
    PLAYER getWinnerPlayer()
    const; // c'est la même chose que getCurrentPlayer() parce que le gagnant est d'office égale au joueur courant
    /**
    * @brief getCurrentPlayer allows to give the current player
    * @return a color of PLAYER enumeration
    */
    PLAYER getCurrentPlayer()
    const; // c'est la même chose que getWinnerPlayer():
    /**
    * @brief getBoard allows you to have the board that includes the game board
    * @return a board
    */
    Board getBoard();
    /**
    * @brief getSoldier allows to get an element of the game at a certain position
    * @param p position where we get the game element
    * @return a gameElement at position
    */
    std::optional<GameElement> getSoldier(Position p);
    /**
    * @brief getState allows to get the state
    * @return a state of STATE enumeration
    */
    STATUS getState() const;
    /**
    * @brief setLevel modifies the level attribute
    */
    void setLevel(LEVEL);
    /**
    * @brief getGameLevel allows to get the level of the game
    * @return a level of LEVEL enumeration
    */
    LEVEL getGameLevel() const;
    /**
    * @brief isFull check if all the pieces have been placed and modify the state to move
    */
    void isFull();
    /**
    * @brief nextPlayerPlacement allows you to change the current player in the PLACE option when the current player has finished placing everything
    */
    void nextPlayerPlacement();
    /**
    * @brief goodFile allows to check if the given file is a good file which respects the 40 pieces
    * @param pieces a vector that includes the game pieces
    * @return a boolean if the file respects the quantity of each piece
    */
    bool goodFile(std::vector<std::string> const & pieces);
};


#endif // GAME_H
