#include "controller/controller.h"
#include <fstream>
#include <algorithm>

#include <iostream>     // rnvs : include / déclaration anticipée
#include "model/game.h" // rnvs : include / déclaration anticipée
#include "view/view.h"  // rnvs : include / déclaration anticipée
#include "keyboardAndStringConvert/keyboard.hpp"    // rnvs : include / déclaration anticipée

using namespace std;

Controller::Controller(Game * model, View * view)
{
    this->model = model;
    this->view = view;
}

void Controller::fillVectorSoldier(vector<GameElement> & soldier,
                                   PLAYER color)
{
    soldier =
    {
        GameElement(MARECHAL, 10, color),
        GameElement(GENERAL, 9, color),
        GameElement(COLONEL, 8, color),
        GameElement(COLONEL, 8, color),
        GameElement(MAJOR, 7, color), GameElement(MAJOR, 7, color), GameElement(MAJOR, 7, color),
        GameElement(COMMANDANT, 6, color), GameElement(COMMANDANT, 6, color), GameElement(COMMANDANT, 6, color), GameElement(COMMANDANT, 6, color),
        GameElement(LIEUTENANT, 5, color), GameElement(LIEUTENANT, 5, color), GameElement(LIEUTENANT, 5, color), GameElement(LIEUTENANT, 5, color),
        GameElement(SERGENT, 4, color), GameElement(SERGENT, 4, color), GameElement(SERGENT, 4, color), GameElement(SERGENT, 4, color),
        GameElement(DEMINEUR, 3, color), GameElement(DEMINEUR, 3, color), GameElement(DEMINEUR, 3, color), GameElement(DEMINEUR, 3, color), GameElement(DEMINEUR, 3, color),
        GameElement(ECLAIREUR, 2, color), GameElement(ECLAIREUR, 2, color), GameElement(ECLAIREUR, 2, color), GameElement(ECLAIREUR, 2, color), GameElement(ECLAIREUR, 2, color), GameElement(ECLAIREUR, 2, color), GameElement(ECLAIREUR, 2, color), GameElement(ECLAIREUR, 2, color),
        GameElement(ESPIONNE, 1, color),
        GameElement(DRAPEAU, -1, color),
        GameElement(BOMBE, 11, color),
        GameElement(BOMBE, 11, color),
        GameElement(BOMBE, 11, color),
        GameElement(BOMBE, 11, color),
        GameElement(BOMBE, 11, color),
        GameElement(BOMBE, 11, color)
    };
}

void Controller::initialiseGameFile()
{
    fstream myFile("battleField.txt");
    if (!myFile)
        cout << "fichier introuvable" << endl;
    string data;
    vector<string> battleField {};
    while (myFile >> data)
        battleField.push_back(data);
    myFile.close();
    if (!model->goodFile(battleField))
    {
        cerr << "Vous n'avez pas la bonne configuration de fichier, veuillez relancer le programme avec le bon nombre de pieces"
             << endl;
        exit(1);
    }
    model->initializeBattelField(battleField);
    view->displayGame();
}

void Controller::initialiseGamePlacement(PLAYER currentPlayer)
{
    array<string, 12> pieceName {"MARECHAL", "GENERAL", "COLONEL", "MAJOR", "COMMANDANT", "LIEUTENANT", "SERGENT", "DEMINEUR", "ECLAIREUR", "ESPIONNE", "DRAPEAU", "BOMBE"};
    fillVectorSoldier(soldierBlue, BLUE);
    fillVectorSoldier(soldierRed, RED);
    view->displayGame();
    for (size_t i = 0 ; i < soldierRed.size(); i++)
    {
        if (currentPlayer == RED)
        {
            cout << "Placer vos soldats joueur ROUGE" << endl;
            cout << "Vous devez placer votre " << pieceName.at(soldierRed.at(
                        i).getRole().value()) << " entrez une position" << endl;
        }
        else
        {
            cout << "Placer vos soldats joueur BLEU" << endl;
            cout << "Vous devez placer votre " << pieceName.at(soldierBlue.at(
                        i).getRole().value()) << " entrez une position" << endl;
        }
        Position p;
        do
        {
            cout << "Attention vous ne pouvez placer que dans votre camps" <<
                 endl;
            p = askPositionPlacement();
        }
        while (!model->canBePlaceStart(p, currentPlayer));
        if (currentPlayer == RED)
            model->initializeBattleField(p, currentPlayer, soldierRed.at(i));
        else
            model->initializeBattleField(p, currentPlayer, soldierBlue.at(i));
        view->displayGame();
    }
}

void Controller::initialiseGame()
{
    LEVEL gameLevel = askLevel();
    model->setLevel(gameLevel);
    string intizalizeMode = askInitializeGame();
    if (intizalizeMode == "FICHIER" )
    {
        initialiseGameFile();
    }
    else if (intizalizeMode == "PLACER")
    {
        initialiseGamePlacement(model->getCurrentPlayer());
        model->nextPlayerPlacement();
        view->displayGame();
        initialiseGamePlacement(model->getCurrentPlayer());
    }
}

int Controller::askDistance()
{
    int distance = -1;
    cout << "Veuillez entrez la distance que l'eclaireur doit parcourir, prenez garde si vous entrez une distance "
         "qui fera que l'eclaireur ce trouvera à l'extérieur celui-ci s'arrêtera juste avant "
         << endl;
    do
    {
        try
        {
            cout << "La distance doit être positive" << endl;
            distance = nvs::lineFromKbd<int>();
        }
        catch (bad_cast const & e)
        {
            cout << "Entrez une bonne distance" << endl;
        }

    }
    while (distance <= 0);
    return distance;
}
bool Controller::conditionPosition(Position pos, Position toGo)
{
    int row = toGo.getX();
    int col = toGo.getY();
    string currentPlayer;
    if (model->getCurrentPlayer() == RED)
    {
        currentPlayer = "RED";
    }
    else
    {
        currentPlayer = "BLUE";
    }
    if (col > 9 || row < 0 || row > 9 || col < 0 )
    {
        cout << "Player " << currentPlayer <<
             " vous ne pouvez pas placer en dehors du champ de bataille" << endl;
        return false;
    }
    if (model->getSoldier(pos)->getRole() == DRAPEAU)
    {
        cout << "Joueur " << currentPlayer << " vous ne pouvez pas deplacer "
             "votre drapeau choisissez de nouveau un soldat à bouger et une direction"
             << endl;
        return false;
    }

    if (model->getSoldier(pos)->getRole() == BOMBE)
    {
        cout << "Joueur " << currentPlayer << " vous ne pouvez pas deplacer "
             "votre bombe choisisez de nouveau un soldat à bouger et une direction"
             << endl;
        return false;
    }
    if (model->getSoldier(toGo)->isWater())
    {
        cout << "Joueur " << currentPlayer <<
             " vous ne pouvez pas deplacer sur de l'eau" << endl;
        return false;
    }
    if (model->getSoldier(toGo) != nullopt &&
            !model->getSoldier(toGo)->isDecor() &&
            model->getSoldier(toGo)->getColor() == model->getCurrentPlayer())
    {
        cout << "Joueur " << currentPlayer <<
             " vous ne pouvez pas deplacer ici, il y a déjà l'un de vos pions" <<
             endl;
        return false;
    }
    return true;
}

void Controller::makeAction()
{
    string currentPlayer;
    if (model->getCurrentPlayer() == RED)
    {
        currentPlayer = "RED";
    }
    else
    {
        currentPlayer = "BLUE";
    }
    cout << "A VOTRE TOUR JOUEUR " << currentPlayer << endl;
    cout << "quels soldat voulez-vous déplacer" << endl;


    Position pos = askPosition();
    DIRECTION dir = askDirection();
    Position direction = directionTs(dir);
    Position toGo = pos + direction;
    while (!conditionPosition(pos, toGo))
    {
        pos = askPosition();
        dir = askDirection();
        direction = directionTs(dir);
        toGo = pos + direction;
    }

    if (model->getSoldier(pos)->getRole() == ECLAIREUR)
    {
        int distance = askDistance();
        try
        {
            saveSoldier = model->move(pos, dir, distance);
        }
        catch (const std::invalid_argument & e)
        {
            cout << e.what() << endl;
        }
    }
    else
    {
        try
        {
            saveSoldier = model->move(pos, dir);
        }
        catch (const std::invalid_argument & e)
        {
            cout << e.what() << endl;
        }
    }
    savePos = pos;
}

Position Controller::askPositionPlacement()
{
    int col {-1};
    int row {-1};
    Position p;
    do
    {
        try
        {
            cout << "Entrez votre position x " << endl;
            col = toupper(nvs::lineFromKbd<char>()) - 64;
            cout << "Entrez votre position y" << endl;
            row = nvs::lineFromKbd<int>();
            p = Position(row - 1, col - 1);
        }
        catch (const exception & e)
        {
            cout << "Vous ne pouvez placer à cette endroit" << endl;
        }
    }
    while (!model->canBePlace(p));

    return p;
}


Position Controller::askPosition()
{
    int col {-1};
    int row {-1};
    Position p;
    do
    {
        try
        {
            cout << "Entrez votre position x" << endl;
            col = toupper(nvs::lineFromKbd<char>()) - 64;
            cout << "Entrez votre position y" << endl;
            row = nvs::lineFromKbd<int>();
            p = Position(row - 1, col - 1);
        }
        catch (const exception & e)
        {
            cout << "Il n y a aucun pions a cette endroit" << endl;
        }
    }
    while (!model->canBeTake(p, model->getCurrentPlayer()));
    return p;
}

DIRECTION Controller::askDirection()
{
    string dir;
    do
    {
        try
        {
            cout << "Entrez votre direction de déplacement, vous avez le choix entre"
                 << endl;
            cout << "GAUCHE - DROITE - HAUT - BAS" << endl;
            dir = nvs::lineFromKbd<string>();
            transform(dir.begin(), dir.end(), dir.begin(), ::toupper);
        }
        catch (const exception & e)
        {

        }
    }
    while (dir != "GAUCHE" && dir != "DROITE" && dir != "HAUT" &&
            dir != "BAS");

    if (dir == "GAUCHE")
    {
        return GAUCHE;
    }
    else if (dir == "DROITE")
    {
        return DROITE;
    }
    else if (dir == "HAUT")
    {
        return HAUT;
    }
    else
    {
        return BAS;
    }
}

Position Controller::directionTs(DIRECTION dir)
{
    Position direction;
    switch (dir)
    {
        case GAUCHE : direction = Position(0, -1);
            break;
        case DROITE : direction = Position(0, +1);
            break;
        case HAUT : direction = Position(-1, 0);
            break;
        case BAS : direction = Position(+1, 0);
            break;
    }

    return direction;
}


LEVEL Controller::askLevel()
{
    string level;
    do
    {
        try
        {
            cout << "Entrez le niveau de votre partie, vous avez le choix entre"
                 << endl;
            cout << "DEBUTANT - NORMAL" << endl;
            level = nvs::lineFromKbd<string>();
            transform(level.begin(), level.end(), level.begin(), ::toupper);
        }
        catch (const exception & e)
        {
            cout << "Entrez un niveau valide" << endl;
        }
    }
    while (level != "DEBUTANT" && level != "NORMAL" );

    if (level == "DEBUTANT")
    {
        return DEBUTANT;
    }
    else
    {
        return NORMAL;
    }
}

string Controller::askInitializeGame()
{
    string mode;
    do
    {
        try
        {
            cout << "Entrez comment voulez-vous initialisé la partie vous avez deux choix"
                 << endl;
            cout << "PLACER - FICHIER" << endl;
            mode = nvs::lineFromKbd<string>();
            transform(mode.begin(), mode.end(), mode.begin(), ::toupper);
        }
        catch (const exception & e)
        {
            cout << "Entrez un bon choix" << endl;
        }
    }
    while (mode != "PLACER" && mode != "FICHIER");

    return mode;
}



void Controller::play()
{
    view->displayWelcome();
    bool gameFinished = false;
    while (!gameFinished)
    {
        switch (model->getState())
        {
            case PLACEMENT:
                initialiseGame();
                break;
            case MOVE:
                makeAction();
                break;
            case TURN_PLAYER:
                model->nextPlayer();
                view->displayGame();
                if (model->getGameLevel() == NORMAL)
                    view->displayAttacker(saveSoldier, savePos);
                break;
            case WIN:
                view->displayWinner();
                gameFinished = true;
                break;
        }
    }
}
