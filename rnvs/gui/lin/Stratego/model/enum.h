#ifndef ENUM_H
#define ENUM_H
/**
* @brief The LEVEL enum represents the possible levels of play
*/
enum LEVEL{
    DEBUTANT,NORMAL
};
/**
* @brief The DIRECTION enum  represent all possible directions in the game
*/
enum DIRECTION{
    GAUCHE,DROITE,HAUT,BAS
};
/**
* @brief The PLAYER enum represent all possible players in the game
*/
enum PLAYER{
    BLUE,RED,NONE
};
/**
* @brief The PIECE enum represents all possible pieces in the game
*/
enum PIECE{
    MARECHAL,GENERAL,COLONEL,MAJOR,COMMANDANT,LIEUTENANT,SERGENT,DEMINEUR,ECLAIREUR,ESPIONNE,DRAPEAU,BOMBE
};
/**
* @brief The STATUS enum represents all state possible in the game
*/
enum STATUS{
    PLACEMENT,WIN,TURN_PLAYER,MOVE
};

#endif // ENUM_H
