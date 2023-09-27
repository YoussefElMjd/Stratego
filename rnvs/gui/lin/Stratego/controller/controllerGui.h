#ifndef CONTROLLERGUI_H
#define CONTROLLERGUI_H

#include "model/game.h"
#include "model/gameElement.h"
#include "view/viewgui.h"
#include <vector>
/**
 * @brief The ControllerGui class is the application controller.
 */
class ControllerGui{
private:
     Game & game;
     ViewGui & view;
    std::vector<GameElement>  soldiers = {
        GameElement(MARECHAL,10),
        GameElement(GENERAL,9),
        GameElement(COLONEL,8),
        GameElement(COLONEL,8),
        GameElement(MAJOR,7),GameElement(MAJOR,7), GameElement(MAJOR,7 ),
        GameElement(COMMANDANT,6),GameElement(COMMANDANT,6),GameElement(COMMANDANT,6 ),GameElement(COMMANDANT,6 ),
        GameElement(LIEUTENANT,5),GameElement(LIEUTENANT,5 ),GameElement(LIEUTENANT,5 ),GameElement(LIEUTENANT,5 ),
        GameElement(SERGENT,4),GameElement(SERGENT,4 ),GameElement(SERGENT,4 ),GameElement(SERGENT,4 ),
        GameElement(DEMINEUR,3),GameElement(DEMINEUR,3 ),GameElement(DEMINEUR,3 ),GameElement(DEMINEUR,3 ),GameElement(DEMINEUR,3 ),
        GameElement(ECLAIREUR,2),GameElement(ECLAIREUR,2 ),GameElement(ECLAIREUR,2 ),GameElement(ECLAIREUR,2 ),GameElement(ECLAIREUR,2 ),GameElement(ECLAIREUR,2 ),GameElement(ECLAIREUR,2 ),GameElement(ECLAIREUR,2 ),
        GameElement(ESPIONNE,1),
        GameElement(DRAPEAU,-1),
        GameElement(BOMBE,11),
        GameElement(BOMBE,11),
        GameElement(BOMBE,11),
        GameElement(BOMBE,11),
        GameElement(BOMBE,11),
        GameElement(BOMBE,11)
    };
public:
    ControllerGui(Game & game, ViewGui & view):game{game},view{view}{};
    /**
     * @brief start Allows to make the link between the view and the controller.
     */
    void start();

};

#endif // CONTROLLERGUI_H
