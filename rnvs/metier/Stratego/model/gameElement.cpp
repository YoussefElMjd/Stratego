#include "model/gameElement.h"

GameElement::GameElement(PIECE role, int power, PLAYER color){
    this->role = role;
    this->power = power;
    this->visible = false;
    this->color = color;
}

GameElement::GameElement(std::string const & decor){
    this->visible = true;
    this->decor = decor;
}

GameElement::GameElement(){
    this->decor = "T";
}

bool GameElement::canBeBeat(GameElement enemy){
    return this->power > enemy.power;
}

void GameElement::setVisible(bool visibility){
    if(this->role != std::nullopt)
        this->visible = visibility;
}

std::optional<bool> GameElement::getVisible() const{
    return this->visible;
}

std::optional<int> GameElement::getPower() const{
    return this->power;
}

std::optional<PIECE> GameElement::getRole() const{
    return this->role;
}

std::optional<PLAYER> GameElement::getColor() const{
    return this->color;
}

std::optional<std::string> GameElement::getDecor() const{
    return this->decor;
}

bool GameElement::isDecor() const{
    return decor != std::nullopt;
}

bool GameElement::isWater() const{
    return isDecor() && decor == "W";
}


