#ifndef VIEWGUI_H
#define VIEWGUI_H

#include <QGraphicsScene>
#include <QMainWindow>
#include <QPushButton>
#include <QKeyEvent>
#include <QLabel>
#include <QSpinBox>
#include <QGridLayout>
#include "model/game.h"
#include "observer/observer.h"
#include <string>
#include <fstream>
class ControllerGui;
QT_BEGIN_NAMESPACE
namespace Ui { class ViewGui; }
QT_END_NAMESPACE

class ViewGui : public QMainWindow, public Observer
{
    Q_OBJECT

    struct Pos { int row = -1, col = -1; };
public:
    ViewGui(Game * game, QWidget *parent = nullptr);
    ~ViewGui();

    inline void controller(ControllerGui * ctrl){
        this->ctrl = ctrl;
        this->game->addObserver(this);
    }
    /**
     * @brief gridPosition Allows to have the position of a widget in a grid.
     * @param widget The widget for which we are looking for the position
     * @return a position with int row and int col
     */
    Pos gridPosition(QWidget * widget);
    /**
     * @brief update Allows to apply the actions made by the state change
     */
    void update() override;
    /**
     * @brief updateBoardMove Allows to fill or update the battlefield
     */
    void updateBoardMove();

    /**
     * @brief getPower Getter of power.
     * @return an integer representing the power
     */
    int getPower() const;

    void keyPressEvent(QKeyEvent *keyEvent)override;
    /**
     * @brief changeInfo Allows you to change the text of a label that informs the player
     * @param info A string that will be used to change the text
     */
    void changeInfo(std::string info);
    /**
     * @brief displayAttacker Allows you to summarize an attack to the player who had the attack
     * @param attacker the soldier who attacks
     * @param p the position of the attack
     */
    void displayAttacker(std::optional<GameElement> attacker);
    /**
     * @brief displayWinner Displays the winner with a pop-up
     */
    void displayWinner();
    /**
     * @brief displayHowPlay Displays who have to play with a pop-up
     */
    void displayWhoPlay();
private slots:
    void on_start_clicked();
    void soldier_clicked();
    void placement_clicked();


private:
    Ui::ViewGui * ui;
    Game * game;
    ControllerGui * ctrl;
    QLabel * blueInfo;
    QLabel * redInfo;
    QSpinBox * redDistance;
    QSpinBox * blueDistance;

    int power;
    PLAYER acutalPlayerButton;
    QPushButton* soldierChoicePlacement;
    std::optional<DIRECTION> dir;
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

    /**
     * @brief placeElement Allows you to place an element in the battlefield.
     * @param pos the position where we will place the element
     * @param nb an integer representing the power
     * @param actualPlayerButton The current player who is BLUE OR RED
     */
    void placeElement(Position pos,int nb, PLAYER actualPlayerButton);

    /**
    * @brief directionTs allows to transforms a direction into a position.
    * @param dir a direction that the player has chosen
    * @return a position which is a transformation from direction to position
    */
    Position directionTs(DIRECTION dir);

    /**
    * @brief conditionPosition Allows you to check all the rules for a position such as being on the board,and position toGo is
    *  not being a bomb or a flag. Do not move towards the water, towards an allied soldier.
    * @param pos p the position where is the soldier that you want to move
    * @param toGo the position where we want to move our soldier
    * @return a boolean if all conditions are met
    */
    bool conditionPosition(Position pos, Position toGo);

    /**
     * @brief initialiseGameFile Allows to initialize a battlefield according to a layout defined in a file.
     */
    void initialiseGameFile();

    void makeMoveView(QPushButton * btn,Position & p);
    void makePlacementView(QGridLayout * topBlue, QGridLayout * bottomRed,Position & p);
    void createLabel();
    void setIcon(std::optional<GameElement>gameElement, QPushButton * soldier);
};
#endif // VIEWGUI_H
