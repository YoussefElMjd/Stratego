#ifndef GAMEELEMENT_H
#define GAMEELEMENT_H
#include "enum.h"
#include <string>
#include <optional>
#include <iomanip>

/**
* @brief The GameElement class represents the elements of the battlefield such as soldiers, bombs, flags or even water
*/
class GameElement{
private:
    std::optional<PIECE> role;
    std::optional<int> power;
    std::optional<bool> visible;
    std::optional<PLAYER> color;
    std::optional<std::string> decor;
public:
    /**
    * @brief GameElement constructor of the class gameElement
    * @param role a role of the PIECE enumeration
    * @param power an integer that represents the power
    * @param color a color of PLAYER enumeration
    */
    GameElement(PIECE role, int power, PLAYER color);
    GameElement(PIECE role, int power);
    /**
    * @brief GameElement constructor of the class gameElement
    * @param decor a decor can be T or W
    */
    GameElement(std::string const & decor);

    GameElement();
    /**
    * @brief canBeBeat Allows to know if the allied soldier can beat an enemy soldier
    * @param enemy with which we check the power
    * @return a boolean if the player's soldier can defeat the enemy's soldier
    */
    bool canBeBeat(GameElement enemy);
    /**
    * @brief setVisible Allows you to change the visible attribute of a soldier
    * @param visibility boolean to which it is necessary to change the visible attribute
    */
    void setVisible(bool visibility);
    /**
    * @brief getVisible allows to have the value of the visible attribute
    * @return a boolean representing the value of the visible attribute
    */
    std::optional<bool> getVisible() const;
    /**
    * @brief getPower Allows to have the value of the power attribute
    * @return an integer that represents the power
    */
    std::optional<int> getPower() const;
    /**
    * @brief getRole Allows to have the value of the role attribute
    * @return a role of the PIECE enumeration
    */
    std::optional<PIECE> getRole() const;
    /**
    * @brief getColor Allows to have the value of the color attribute
    * @return a color of PLAYER enumeration
    */
    std::optional<PLAYER> getColor() const;
    /**
    * @brief getDecor Allows to have the value of the decor attribute
    * @return a string representing the decor
    */
    std::optional<std::string> getDecor()const;
    /**
    * @brief isDecor Allows to know if an element of the game is a decor
    * @return a boolean if it's a decor oh the game
    *
    */
    bool isDecor() const;
    /**
    * @brief isWater Allows to know if an element of the game is a water
    * @return a boolean if it's a decor oh the game
    */
    bool isWater() const;
};
inline std::ostream& operator<<(std::ostream& os, GameElement const & dt){
    if(!dt.isDecor()){
        if(dt.getRole().value()== BOMBE){
            os << std::setw(2)<< "B";
        }else if(dt.getRole().value()==DRAPEAU){
            os << std::setw(2)<< "D";
        } else {
            os << std::setw(2) << dt.getPower().value();
        }
    } else {
        if(dt.isWater()){
            os << std::setw(3) << "W" << std::setw(2) << "";
        } else {
            os << std::setw(3) << " " << std::setw(2) << "";
        }
    }
    return os;
}


#endif // GAMEELEMENT_H
