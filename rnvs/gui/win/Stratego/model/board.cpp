#include "model/board.h"
using namespace std;

Board::Board(){
    for(size_t i = 0 ; i < water.size(); i++){
        battleField[water[i].getX()][water[i].getY()] = GameElement("W");
    }
}

void Board::mirrorVector(std::vector<std::string> &s){
    for(int i = 0 ; i < 10;i++){
        string swapValue = s.at(i);
        s.at(i) = s.at(i+30);
        s.at(i+30) = swapValue;
    }
    for(int i = 10 ; i < 20;i++){
        string swapValue = s.at(i);
        s.at(i) = s.at(i+10);
        s.at(i+10) = swapValue;
    }
}

void Board::fillArray(int power, PLAYER player,int row, int col){
    switch(power){
    case 10 :battleField[row][col] = GameElement(MARECHAL,power,player);
        break;

    case 9 :battleField[row][col] = GameElement(GENERAL,power,player);
        break;

    case 8 :battleField[row][col] = GameElement(COLONEL,power,player);
        break;

    case 7 :battleField[row][col] = GameElement(MAJOR,power,player);
        break;

    case 6 :battleField[row][col] = GameElement(COMMANDANT,power,player);
        break;

    case 5 :battleField[row][col] = GameElement(LIEUTENANT,power,player);
        break;

    case 4 :battleField[row][col] = GameElement(SERGENT,power,player);
        break;

    case 3 :battleField[row][col] = GameElement(DEMINEUR,power,player);
        break;

    case 2 :battleField[row][col] = GameElement(ECLAIREUR,power,player);
        break;

    case 1 :battleField[row][col] = GameElement(ESPIONNE,power,player);
        break;
    }

}

void Board::initializeBattleField(vector<string> s, PLAYER player){
    if(player == BLUE){
        int row = -1;
        int col = 0;
        for(size_t i = 0; i < s.size() && row < 5;i++){
            if(i%10 == 0){
                row++;
                col = 0;
            }
            if(s.at(i) == "B"){
                battleField[row][col] = GameElement(BOMBE,11,player);
            } else if(s.at(i) == "D"){
                battleField[row][col] = GameElement(DRAPEAU,-1,player);
            } else {
                int power = stoi(s.at(i));
                fillArray(power,player,row,col);
            }
            col++;
        }
    } else if(player == RED){
        mirrorVector(s);
        int row = 5;
        int col = 0;

        for(size_t i = 0; i < s.size() && row < 10;i++){
            if(i%10 == 0){
                row++;
                col = 0;
            }
            if(s.at(i) == "B"){
                battleField[row][col] = GameElement(BOMBE,11,player);
            } else if(s.at(i) == "D"){
                battleField[row][col] = GameElement(DRAPEAU,-1,player);
            } else {
                int power = stoi(s.at(i));
                fillArray(power,player,row,col);
            }
            col++;
        }
    }
}

void Board::initializeBattleField(Position p, PLAYER player, GameElement s){
    if(canBePlaceStart(p,player)){
        battleField[p.getX()][p.getY()] = s;
    }
}

bool Board::canBePlaceStart(Position p, PLAYER player){
    int row = p.getX();
    int col = p.getY();

    if(col > 10 || row < 0 || col < 0 || row > 10)
        return false;

    if(player == BLUE){
        if(row >= 0 && row <= 3){
            if(!battleField[row][col].isWater()){
                return true;
            }else{
                return false;
            }
        }
    }
    if(player == RED){
        if(row >= 6 && row <= 9){
            if(!battleField[row][col].isWater()){
                return true;
            }else{
                return false;
            }
        }

    }
    return false;
}

void Board::removeFromBattle(const Position & p){
    int row = p.getX();
    int col = p.getY();
    battleField[row][col] = GameElement("T");
}

int Board::endGame(){
    int cptBlue = 0;
    int cptRed = 0;
    int cptDrapeau = 0;

    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            if(battleField[i][j].getRole() == DRAPEAU){
                cptDrapeau++;
            }
            if(battleField[i][j].getColor() == RED){
                if(battleField[i][j].getRole() != BOMBE && battleField[i][j].getRole() != DRAPEAU){
                    cptRed++;
                }
            } else if(battleField[i][j].getColor() == BLUE){
                if(battleField[i][j].getRole() != BOMBE && battleField[i][j].getRole() != DRAPEAU){
                    cptBlue++;
                }

            }
        }
    }

    if(cptDrapeau < 2)
        return 1;
    if(cptRed < 1)
        return 2;
    if(cptBlue < 1)
        return 3;
    else
        return 0;

}

bool Board::moveEclaireur(Position & p, Position & toGo, Position dir, int distance){
    int i = 0;
    while(canBePlace(toGo) && i < distance){
        battleField[toGo.getX()][toGo.getY()] = battleField[p.getX()][p.getY()];
        removeFromBattle(p);
        i++;
        p = toGo;
        toGo+=dir;
    }
    int row = toGo.getX();
    int col = toGo.getY();
    if(col < 10 && row >= 0 && row < 10 && col >= 0){
        if(i<distance && !getSoldier(toGo).isDecor() && getSoldier(toGo).getColor() != getSoldier(p).getColor()){
            return true;
        }
    }
    return false;
}

bool Board::canBePlace(const Position & p){
    int row = p.getX();
    int col = p.getY();
    if(col > 9 || row < 0 || row > 9 || col < 0 )
        return false;

    if(!getSoldier(p).isDecor()){
        return false;
    }

    Position waterPos;
    for(size_t i = 0 ; i < this->water.size();i++){
        waterPos = water[i];
        if(row == waterPos.getX() && col == waterPos.getY()){
            return  false;
        }
    }
    return true;
}

std::optional<GameElement> Board::move(Position p, DIRECTION dir, int distance){
    if(!getSoldier(p).isDecor() && getSoldier(p).getRole() != DRAPEAU && getSoldier(p).getRole() != BOMBE){
        Position direction;
        switch(dir){
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
        std::optional<GameElement> saveSoldier;
        if(distance == 1){
            if(canBePlace(toGo)){
                battleField[toGo.getX()][toGo.getY()] = battleField[p.getX()][p.getY()];
                removeFromBattle(p);
            } else {
                if(!getSoldier(toGo).isDecor() && getSoldier(toGo).getColor() != getSoldier(p).getColor()){
                    saveSoldier = attack(p,toGo);
                    return saveSoldier;
                }
            }
        } else if(distance > 1 && getSoldier(p).getRole() == ECLAIREUR){
            bool iNeedToAttack = moveEclaireur(p,toGo,direction,distance);
            if(iNeedToAttack == true){
                reveal(p);
                reveal(toGo);
                saveSoldier = attack(p,toGo);
                return saveSoldier;
            }
        }
    }
    return nullopt;
}

bool Board::canBeTake(const Position & pos, PLAYER player){
    if(pos.getY() > 9 || pos.getX() < 0 || pos.getX() > 9 || pos.getY() < 0 )
        return false;

    if(battleField[pos.getX()][pos.getY()].isDecor())
        return false;

    if(battleField[pos.getX()][pos.getY()].getColor() != player)
        return false;

    return true;
}

GameElement Board::attack(Position p , Position toAttack){
    GameElement s1 =  getSoldier(p);
    GameElement s2 = getSoldier(toAttack);
    getSoldier(p).setVisible(true);
    getSoldier(toAttack).setVisible(true);
    if(s1.getRole() == DEMINEUR && s2.getRole() == BOMBE){
        battleField[toAttack.getX()][toAttack.getY()] = battleField[p.getX()][p.getY()];
        removeFromBattle(p);
    } else if(s1.getRole() != DEMINEUR && s2.getRole() == BOMBE){
        removeFromBattle(p);
    } else if(s1.getRole() == ESPIONNE && s2.getRole() == MARECHAL){
        battleField[toAttack.getX()][toAttack.getY()] = battleField[p.getX()][p.getY()];
        removeFromBattle(p);
    }else if((s2.getRole() == ESPIONNE && s1.getRole() == MARECHAL)){
        removeFromBattle(p);
    }else if(s1.canBeBeat(s2)){
        battleField[toAttack.getX()][toAttack.getY()] = battleField[p.getX()][p.getY()];
        removeFromBattle(p);
    }else if(s2.canBeBeat(s1)){
        removeFromBattle(p);
    }else if(s1.getPower().value() == s2.getPower().value()){
        removeFromBattle(toAttack);
        removeFromBattle(p);
    }
    return s1;
}

void Board::reveal(Position p){
    GameElement & soldier = getSoldier(p);
    if(soldier.getRole() != std::nullopt)
        soldier.setVisible(true);
}

void Board::unReveal(Position p){
    GameElement & soldier = getSoldier(p);
    if(soldier.getRole() != std::nullopt)
        soldier.setVisible(false);
}

GameElement & Board::getSoldier(const Position & pos){
    return battleField[pos.getX()][pos.getY()];
}

bool Board::isFull(){
    int cpt = 0;
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            if(!battleField[i][j].isDecor()){
                cpt++;
            }
        }
    }
    if(cpt == 80){
        return true;
    }
    return false;
}
