#include "view/view.h"
using namespace std;
using namespace nvs;
View::View(Game * model){
    this->model = model;

}

void View::displayWelcome(){
    cout<< "********************************"<< endl;
    cout << "STRATEGO                   V1.0 " << endl;
    cout<< "********************************"<< endl;
}

void View::displayGame(){
    for(int i = 0; i < 25; i++){
        cout << endl;
    }
    cout << setw(3) << " " << setw(2) << "";
    for(size_t i = 65 ; i <= 74; i++){
        char asciiCharacter = i;
        cout << setw(3) << asciiCharacter << setw(2) << "";
    }
    cout << endl;
    cout << endl;
    for(size_t i = 0; i < 10 ; i++){
        cout << setw(3) << i+1 << setw(2) << "";
        for(size_t j = 0; j < 10; j++){
            if(model->getSoldier(Position(i,j)) == nullopt){
                if(model->getCurrentPlayer() == RED){
                    cout << std::setw(3) << "B" << std::setw(2) << "*";
                } else {
                    cout << std::setw(3) << "R" << std::setw(2) << "*";
                }
            } else {
                if(model->getSoldier(Position(i,j)).value().getColor() == BLUE){
                    cout << std::setw(3) << "B" << model->getSoldier(Position(i,j)).value();
                } else if(model->getSoldier(Position(i,j)).value().getColor() == RED){
                    cout << std::setw(3) << "R" << model->getSoldier(Position(i,j)).value();
                } else {
                    cout << std::setw(3) << model->getSoldier(Position(i,j)).value();
                }
            }
        }
        cout << endl;
    }
    cout << endl;
}

void View::displayAttacker(std::optional<GameElement> soldier, Position pos){
    if(soldier != nullopt){
        char y = pos.getY()+65;
        string role;
        switch(soldier->getRole().value()){
        case MARECHAL :
            role = "MARECHAL";
            break;
        case GENERAL:
            role = "GENERAL";
            break;
        case COLONEL:
            role = "COLONEL";
            break;
        case MAJOR:
            role = "MAJOR";
            break;
        case COMMANDANT:
            role = "COMMANDANT";
            break;
        case LIEUTENANT:
            role = "LIEUTENANT";
            break;
        case SERGENT:
            role = "SERGENT";
            break;
        case  DEMINEUR :
            role = "DEMINEUR";
            break;
        case ECLAIREUR:
            role = "ECLAIREUR";
            break;
        case ESPIONNE:
            role = "ESPIONNE";
            break;
        case DRAPEAU:
            role = "DRAPEAU";
            break;
        case BOMBE :
            role = "BOMBE";
            break;
        }

        if(model->getCurrentPlayer() == BLUE){
            if(role == "BOMBE"){
                cout << "!!!! BOUMMMMMMMMMMMMM VOTRE SOLDAT EST MORT D'UNE BOMBE !!!!" << endl;
            } else {
                cout << "!!!! LE JOUEUR ROUGE VOUS A ATTAQUÉ AVEC " << role << " PUISSANCE" << soldier.value()
                     << " DEPUIS LA POSITION " << y << pos.getX()+1 << "!!!" << std::endl;
            }
        } else {
            if(role == "BOMBE"){
                cout << "!!!! BOUMMMMMMMMMMMMM VOTRE SOLDAT EST MORT D'UNE BOMBE !!!!" << endl;
            } else {
                cout << "!!!! LE JOUEUR BLEU VOUS A ATTAQUÉ AVEC " << role << " PUISSANCE" << soldier.value()
                     << " DEPUIS LA POSITION " << y << pos.getX()+1 << "!!!" << std::endl;
            }
        }
    }
}

void View::displayWinner(){
    if(model->getWinnerPlayer() == BLUE){
        cout << "LE GAGNANT EST LE JOUEUR BLEU" << endl;
    } else {
        cout << "LE GAGNANT EST LE JOUEUR RED" << endl;
    }
}
