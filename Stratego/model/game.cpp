#include "game.h"
#include <map>
using namespace std;
Game::Game(Board & board, LEVEL level){
    this->gameLevel = level;
    this->board = &board;
    this->state = PLACEMENT;
    this->currentPlayer = RED;
}

void Game::initializeBattelField(const vector<string> & file){
    if(this->state != PLACEMENT){
        invalid_argument("Le status n'est pas à PLACEMENT");
    }
    board->initializeBattleField(file,RED);
    board->initializeBattleField(file,BLUE);
    this->state = MOVE;
    notify();
}

void Game::initializeBattleField(const Position & p, PLAYER player,const GameElement & s){
    if(this->state != PLACEMENT){
        invalid_argument("Le status n'est pas à PLACEMENT");
    }
    board->initializeBattleField(p,player,s);
    isFull();
    notify();
}

bool Game::canBePlace(const Position & p){
    if(this->state != MOVE){
        invalid_argument("Le status n'est pas à move");
    }
    return board->canBePlace(p);
}

bool Game::canBePlaceStart(const Position & p, PLAYER player){
    if(this->state != PLACEMENT){
        invalid_argument("Le status n'est pas à placement");
    }
    return board->canBePlaceStart(p,player);
}

bool Game::canBeTake(const Position & pos, PLAYER player){
    if(this->state != MOVE){
        invalid_argument("Le status n'est pas à move");
    }
    return board->canBeTake(pos,player);
}

bool Game::checkCanMakeMove(vector<string> & movement){
    if(this->state != MOVE){
        invalid_argument("Le status n'est pas à move");
    }
    string go = movement.at(0);
    string back = movement.at(1);
    for(size_t i =2 ; i < movement.size(); i+=2){
        if(go != movement.at(i)){
            movement.erase(movement.cbegin(),movement.cbegin()+i);
            return true;
        }
        if(back != movement.at(i+1)){
            movement.erase(movement.cbegin(),movement.cbegin()+i);
            return true;
        }
    }
    movement.pop_back();
    return false;
}
void Game::fillMovementList(bool &canMakeMove,Position toGo){
    if(this->currentPlayer == RED){
        movementRed.push_back(toGo.tostring());
        if(movementRed.size() == 8)
            canMakeMove = checkCanMakeMove(movementRed);
    } else if(this->currentPlayer == BLUE){
        movementBlue.push_back(toGo.tostring());
        if(movementBlue.size() == 8){
            canMakeMove = checkCanMakeMove(movementBlue);
        }
    }
}

void Game::makeMove(optional<GameElement> & saveSoldier,Position p, Position direction, DIRECTION d,int distance){
    if(this->currentPlayer == RED){
        saveSoldier = board->move(p,d,distance);
        oldSoldierRED = &board->getSoldier(p+direction);
    } else {
        saveSoldier = board->move(p,d,distance);
        oldSoldierBLUE = &board->getSoldier(p+direction);
    }
}

void Game::clearMovementList(const Position p){
    if(this->currentPlayer == RED){
        if(oldSoldierRED != nullopt){
            GameElement * old = oldSoldierRED.value();
            GameElement * actual = &board->getSoldier(p);
            if(old != actual){
                movementRed.clear();
            }
        }
    } else {
        if(oldSoldierBLUE != nullopt){
            GameElement * old = oldSoldierBLUE.value();
            GameElement * actual = &board->getSoldier(p);;
            if(old != actual){
                movementBlue.clear();
            }
        }
    }
}

optional<GameElement> Game::move(Position & p, DIRECTION & d, int distance){
    if(this->state != MOVE){
        invalid_argument("Le status n'est pas à MOVE");
    }

    bool canMakeMove = true;
    Position direction;
    switch(d){
    case GAUCHE : direction = Position(0,-1);
        break;
    case DROITE : direction = Position(0,+1);
        break;
    case HAUT : direction = Position(-1,0);
        break;
    case BAS : direction = Position(+1,0);
        break;
    }
    Position toGo = p+direction;

    optional<GameElement> saveSoldier;
    clearMovementList(p);
    fillMovementList(canMakeMove,toGo);
    if(canMakeMove){
        makeMove(saveSoldier,p,direction,d,distance);
        if(this->gameLevel == NORMAL){
            unReveal(p);
            unReveal(p+direction);
        }
    } else {
        throw invalid_argument("tu peut pas te déplacer car tu est entrain de faire trois aller retour consécutif");
    }

    int whatIsTheEnd = endGame();
    switch(whatIsTheEnd){
    case 1 :
        this->state = WIN;
        break;
    case 2 :
        this->currentPlayer = BLUE;
        this->state = WIN;
        break;
    case 3:
        this->currentPlayer = RED;
        this->state = WIN;
        break;
    default:
        this->state = TURN_PLAYER;
    }
    notify();

    return saveSoldier;
}
void Game::nextPlayerPlacement(){
    if(this->state != PLACEMENT)
        invalid_argument("Le status n'est pas à PLACEMENT");

    if(this->currentPlayer == RED){
        this->currentPlayer = BLUE;
    } else {
        this->currentPlayer = RED;
    }
}

void Game::nextPlayer(){
    if(this->state != TURN_PLAYER)
        invalid_argument("Le status n'est pas à TURN_PLAYER");

    if(this->currentPlayer == RED){
        this->currentPlayer = BLUE;
    } else {
        this->currentPlayer = RED;
    }

    this->state = MOVE;
}

int Game::endGame(){
    if(this->state != MOVE)
        invalid_argument("Le status n'est pas à MOVE");
    return board->endGame();
}

PLAYER Game::getWinnerPlayer() const{
    if(this->state != WIN)
        invalid_argument("Le status n'est pas à WIN");
    return this->currentPlayer;
}

PLAYER Game::getCurrentPlayer() const{
    return this->currentPlayer;
}

optional<GameElement> Game::getSoldier(Position p){
    const GameElement & element = board->getSoldier(p);
    if(this->currentPlayer == BLUE){
        if(element.getVisible() == false && element.getColor() != BLUE){
            return nullopt;
        }
        return board->getSoldier(p);
    }
    if(this->currentPlayer == RED){
        if(element.getVisible() == false && element.getColor() != RED){
            return nullopt;
        }
        return board->getSoldier(p);
    }
    return nullopt;
}
Board Game::getBoard() const{
    return *this->board;
}
STATUS Game::getState() const{
    return this->state;
}

void Game::reveal(const Position & p){
    GameElement & soldier = board->getSoldier(p);
    if(soldier.getRole() != nullopt)
        soldier.setVisible(true);
}

void Game::unReveal(const Position & p){
    GameElement & soldier = board->getSoldier(p);
    if(soldier.getRole() != nullopt)
        soldier.setVisible(false);
}

void Game::setLevel(LEVEL level){
    if(this->state != PLACEMENT){
        invalid_argument("Le status n'est pas à placement");
    }
    this->gameLevel = level;
}

LEVEL Game::getGameLevel() const{
    return this->gameLevel;
}

void Game::isFull(){
    if(this->state != PLACEMENT){
        invalid_argument("Le status n'est pas à placement");
    }
    if(board->isFull()){
        if(this->currentPlayer == RED){
            this->currentPlayer = BLUE;
        } else {
            this->currentPlayer = RED;
        }
        this->state = MOVE;
    }

}
bool Game::goodFile(vector<string> const & pieces){
    map<string,int> numberPiece {};

    for(size_t i = 0; i < pieces.size(); i++){
        auto it = numberPiece.find(pieces.at(i));
        if(it == numberPiece.end()){
            numberPiece.insert(pair<string,int>{pieces.at(i),1});
        } else {
            auto value = numberPiece.find(pieces.at(i));
            value->second+=1;
        }
    }
    map<string, int> realNumberPiece {{"10",1},{"9",1},{"8",2},{"7",3},{"6",4},{"5",4},{"4",4},{"3",5},{"2",8},{"1",1},{"D",1},{"B",6}};
    return numberPiece.size() == realNumberPiece.size() && equal(numberPiece.begin(),numberPiece.end(),realNumberPiece.begin());

}

