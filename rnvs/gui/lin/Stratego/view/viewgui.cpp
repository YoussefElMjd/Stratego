#include "viewgui.h"
#include "ui_viewgui.h"
#include <QMessageBox>
#include "controller/controllerGui.h"
#include <QFileDialog>

using namespace std;

ViewGui::ViewGui(Game * game, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ViewGui), game{game},power{0},acutalPlayerButton{NONE}
{
    ui->setupUi(this);
    this->setWindowTitle("Stratego - Youssef & Aimen");
    this->setWindowIcon(QIcon(":/ressources/logo.png"));
    this->grabKeyboard();
    this->blueInfo = nullptr;
    this->redInfo = nullptr;

}
ViewGui::~ViewGui()
{
    delete ui;

}


void ViewGui::on_start_clicked()
{
    bool isDebutant = ui->debutant->isChecked();
    bool isNormal = ui->normal->isChecked();
    bool isPlacement = ui->placement->isChecked();
    bool isFile = ui->file->isChecked();
    ui->groupBox->close();
    ui->background->hide();
    delete ui->background;
    delete  ui->groupBox;

    if(isDebutant){
        this->game->setLevel(DEBUTANT);
    } else if(isNormal) {
        this->game->setLevel(NORMAL);
    }

    QGridLayout * battleField = ui->battleField;
    QLabel * backgroundBattle = ui->backgroundbattle;
    backgroundBattle->setStyleSheet("background: url(:/ressources/battlefield.png)");
    battleField->setContentsMargins(0,0,0,0);
    battleField->setSpacing(1);
    const QSize emptySize = QSize(97, 60);
    for(int i = 0 ; i < 10 ; i++){
        for(int j = 0; j < 10; j++){
            QPushButton * empty = new QPushButton();
            empty->setObjectName(QString("soldier"));
            connect(empty, SIGNAL(clicked()), this, SLOT(soldier_clicked()));
            if(this->game->getSoldier(Position(i,j))->isWater()){
                empty->setStyleSheet("background-color:transparent; border:none; ");
                empty->setDisabled(true);
            }else {
                empty->setStyleSheet("background-color:transparent; border:1px solid; border-color:green;");
            }
            empty->setFixedSize(emptySize);
            battleField->addWidget(empty,i,j);
        }
    }
    if(isPlacement){
        QGridLayout * topBlue = ui->top;
        QGridLayout * bottomRed= ui->bottom;
        topBlue->setContentsMargins(0,0,0,0);
        bottomRed->setContentsMargins(0,0,0,0);
        topBlue->setSpacing(0);
        bottomRed->setSpacing(0);
        int index = 0;
        for(int i = 0 ; i < 4 ; i++){
            for(int j = 0; j < 10; j++){
                QPushButton * soldierBlue = new QPushButton(QString::number(this->soldiers.at(index).getPower().value()));
                QPushButton * soldierRed = (new QPushButton(QString::number(this->soldiers.at(index).getPower().value())));
                soldierBlue->setAccessibleName("BLUE");
                soldierBlue->setDisabled(true);
                soldierRed->setAccessibleName("RED");
                connect(soldierBlue, SIGNAL(clicked()), this, SLOT(placement_clicked()));
                connect(soldierRed, SIGNAL(clicked()), this, SLOT(placement_clicked()));
                soldierBlue->setStyleSheet("border: 4px solid; border-color: blue; color: white;background-color:rgb(73, 110, 236)");
                soldierRed->setStyleSheet("border: 4px solid; border-color: red; color: white;background-color:rgb(236, 73, 73)");
                topBlue->addWidget(soldierBlue,i,j);
                bottomRed->addWidget(soldierRed,i,j);
                index++;
            }
        }
    }else if(isFile){
        this->initialiseGameFile();
        QMessageBox msgBox;
        msgBox.information(this,"Qui commmence ?","Le joueur RED commence ! ");
    }
}

ViewGui::Pos ViewGui::gridPosition(QWidget * widget) {
    if (! widget->parentWidget()) return {};
    auto layout = qobject_cast<QGridLayout*>(widget->parentWidget()->layout());
    if (! layout) return {};
    int index = layout->indexOf(widget);
    Q_ASSERT(index >= 0);
    int _;
    Pos pos;
    layout->getItemPosition(index, &pos.row, &pos.col, &_, &_);
    return pos;
}

void ViewGui::soldier_clicked(){
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    Pos position = gridPosition(btn);
    Position p (position.row,position.col);
    QGridLayout * bottomRed= ui->bottom;
    QGridLayout * topBlue = ui->top;
    if(this->game->getState() == PLACEMENT){
        makePlacementView(topBlue,bottomRed,p);
    } else if(this->game->getState() == MOVE){
        makeMoveView(btn,p);
    }
}

void ViewGui::makeMoveView(QPushButton * btn,Position & p){
    if(this->game->canBeTake(p,this->game->getCurrentPlayer())){
        if(!dir.has_value()){
            changeInfo("Vous devez d'abord entrez une touche au clavier");
        }else {
            if(conditionPosition(p,p+directionTs(this->dir.value()))){
                std::optional<GameElement> attacker;
                if(btn->text().toInt() == 2){
                    if(this->game->getCurrentPlayer() == RED && redDistance->value() != 0){
                        attacker = this->game->move(p,dir.value(),redDistance->value());

                    }else if(blueDistance->value() != 0){
                        attacker = this->game->move(p,dir.value(),blueDistance->value());
                    }else{
                        changeInfo("N'oubliez pas d'indiquez la distance pour l'éclaireur");
                    }
                } else {
                    try {
                        attacker = this->game->move(p,dir.value());
                    }  catch (const invalid_argument & e) {
                        changeInfo("Vous ne pouvez pas faire plus de trois aller retour consécutif");
                    }
                }
                this->dir = nullopt;
                if(this->game->getGameLevel() == NORMAL){
                    displayAttacker(attacker);
                }
            }
        }
    }
}
void ViewGui::makePlacementView(QGridLayout * topBlue, QGridLayout * bottomRed,Position & p){
    if(this->game->canBePlaceStart(p,this->acutalPlayerButton) && this->game->canBePlace(p)){
               this->placeElement(p,this->power,this->acutalPlayerButton);
               this->soldierChoicePlacement->close();
               delete this->soldierChoicePlacement;
               this->power = 0;
               this->acutalPlayerButton = NONE;

               if(topBlue->count() == 40 && bottomRed->isEmpty()){
                   QMessageBox msgBox;
                   msgBox.information(this,"A qui le tour ?","Le joueur BLEU doit placer ses pions ! ");
                   for(int i = 0 ; i < 4 ; i++){
                       for(int j = 0; j < 10; j++){
                           QLayoutItem* item = topBlue->itemAtPosition(i, j);
                           QWidget * widget = item->widget();
                           QPushButton * soldier = dynamic_cast<QPushButton*>(widget);
                           soldier->setDisabled(false);
                       }
                   }
               }
           }else if(this->acutalPlayerButton == NONE){
               QMessageBox messageBox;
               messageBox.critical(0,"Error","Vous devez choisir un soldat à placer");
               messageBox.setFixedSize(500,200);

           } else {
               QMessageBox messageBox;
               messageBox.critical(0,"Error","Vous ne pouvez pas placer a cette endroit");
               messageBox.setFixedSize(500,200);

           }

}

void ViewGui::placement_clicked(){
    this->soldierChoicePlacement = qobject_cast<QPushButton*>(sender());
    int nb = soldierChoicePlacement->text().toInt();
    PLAYER actualPlayerButton;
    if(soldierChoicePlacement->accessibleName().toStdString() == "BLUE"){
        actualPlayerButton = BLUE;
    } else {
        actualPlayerButton = RED;
    }
    this->power = nb;
    this->acutalPlayerButton = actualPlayerButton;
}

int ViewGui::getPower() const
{
    return power;
}

void ViewGui::update(){
    switch (game->getState()) {
    case PLACEMENT:
        if(ui->top->count() == 40 && ui->bottom->count() == 1){
            this->game->nextPlayerPlacement();
        }
        updateBoardMove();
        break;
    case MOVE:
        if(this->blueInfo == nullptr && this->redInfo == nullptr){
            createLabel();
        }
        updateBoardMove();
        break;
    case TURN_PLAYER:
        this->game->nextPlayer();
        displayWhoPlay();
        updateBoardMove();
        break;
    case WIN:
        displayWinner();
        close();
        break;
    }
}
void ViewGui::keyPressEvent(QKeyEvent *keyEvent){
    switch (keyEvent->key()) {
    case Qt::Key_Down:
        this->dir = BAS;
        changeInfo("Direction choisi: BAS");
        break;
    case Qt::Key_Left:
        this->dir = GAUCHE;
        changeInfo("Direction choisi: GAUCHE");
        break;
    case Qt::Key_Right:
        this->dir = DROITE;
        changeInfo("Direction choisi: DROITE");
        break;
    case Qt::Key_Up:
        this->dir = HAUT;
        changeInfo("Direction choisi: HAUT");
        break;
    default:
        break;
    }
}
void ViewGui::updateBoardMove(){
    QGridLayout * battleField = ui->battleField;
    for(int i = 0 ; i < 10 ; i++){
        for(int j = 0; j < 10; j++){
            std::optional<GameElement>gameElement = this->game->getSoldier(Position(i,j));
            QLayoutItem* item = battleField->itemAtPosition(i, j);
            QWidget * widget = item->widget();
            QPushButton * soldier = dynamic_cast<QPushButton*>(widget);
            if(gameElement == nullopt){
                if(game->getCurrentPlayer() == RED){
                    if(game->getState() != PLACEMENT){
                        soldier->setStyleSheet("background-color:transparent;color: rgb(73, 110, 236); font-size:50px;");
                    }else{
                        soldier->setStyleSheet("background-color:transparent;color: rgb(73, 110, 236); border: 1px solid; font-size:50px;");
                    }
                    soldier->setStyleSheet("background-color:transparent;color: rgb(73, 110, 236);font-size:50px;");
                    soldier->setText("?");
                    soldier->setIcon(QIcon(""));
                } else {
                    soldier->setStyleSheet("background-color:transparent;color: rgb(236, 73, 73);font-size:50px;");
                    soldier->setText("?");
                    soldier->setIcon(QIcon(""));
                }
            } else if(gameElement->getColor() == BLUE){
                setIcon(gameElement,soldier);
                soldier->setStyleSheet("color: rgb(73, 110, 236); background-color:transparent;font-size:15px; font-style:bold;");
                soldier->setText(QString::number(gameElement->getPower().value()));
                soldier->setAccessibleName("BLUE");
                soldier->setIconSize(QSize(60, 50));
            } else if(gameElement->getColor() == RED){
                setIcon(gameElement,soldier);
                soldier->setStyleSheet("color: rgb(236, 73, 73); background-color:transparent;font-size: 15px; font-style:bold;");
                soldier->setText(QString::number(gameElement->getPower().value()));
                soldier->setAccessibleName("RED");
                soldier->setIconSize(QSize(60, 50));
            } else {
                if(!gameElement->isWater()){
                    if(game->getState() == MOVE){
                        soldier->setStyleSheet("background-color:transparent;");
                    } else{
                        soldier->setStyleSheet("background-color:transparent; border:1px solid;border-color:green;");
                    }
                    soldier->setText("");
                    soldier->setAccessibleName("");
                    soldier->setIcon(QIcon(""));
                }else {
                    soldier->setStyleSheet("background-color:transparent;");
                    soldier->setDisabled(true);
                    soldier->setIcon(QIcon(""));
                }
            }
        }
    }
}
void ViewGui::createLabel(){
    blueInfo = new QLabel("BLUE");
    redInfo = new QLabel("RED");
    blueInfo->setStyleSheet("color:rgb(19, 73, 255); font-size:20px");
    redInfo->setStyleSheet("color:rgb(255, 19, 19); font-size:20px");
    blueInfo->setAlignment(Qt::AlignCenter);
    redInfo->setAlignment(Qt::AlignCenter);
    blueInfo->setObjectName("blueInfo");
    redInfo->setObjectName("redInfo");
    redDistance = new QSpinBox();
    blueDistance = new QSpinBox();
    redDistance->setAlignment(Qt::AlignCenter);
    blueDistance->setAlignment(Qt::AlignCenter);
    ui->top->addWidget(blueInfo);
    ui->top->addWidget(blueDistance);
    ui->bottom->addWidget(redInfo);
    ui->bottom->addWidget(redDistance);
}
void ViewGui::displayWinner(){
    ui->gridLayoutWidget->setDisabled(true);
    this->releaseKeyboard();
    if(this->game->getCurrentPlayer() == BLUE){
        QMessageBox msgBox;
        msgBox.information(this,"Qui a gagné ?","Le joueur BLEU a gagné ! ");
    }else {
        QMessageBox msgBox;
        msgBox.information(this,"Qui a gagné ?","Le joueur ROUGE a gagné ! ");
    }
}
void ViewGui::changeInfo(std::string info){
    if(this->blueInfo != nullptr && this->redInfo != nullptr){
        if(this->game->getCurrentPlayer() == BLUE){
            this->blueInfo->setText(QString::fromStdString(info));
        } else{
            this->redInfo->setText(QString::fromStdString(info));
        }
    }
}

void ViewGui::displayAttacker(std::optional<GameElement> attacker){
    if(attacker != nullopt){
        string role;
        switch(attacker->getRole().value()){
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
        string power = std::to_string(attacker.value().getPower().value());
        if(game->getCurrentPlayer() == BLUE){
            if(role == "BOMBE"){
                blueInfo->setText("!!!! BOUMMMMMMMMMMMMM VOTRE SOLDAT EST MORT D'UNE BOMBE !!!!");
            } else {
                string info = "!!!! LE JOUEUR ROUGE VOUS A ATTAQUÉ AVEC " + role + " PUISSANCE " + power +" !!!";
                blueInfo->setText(QString::fromStdString(info));
            }
        } else {
            if(role == "BOMBE"){
                redInfo->setText("!!!! BOUMMMMMMMMMMMMM VOTRE SOLDAT EST MORT D'UNE BOMBE !!!! ");
            } else {
                string info = "!!!! LE JOUEUR BLEU VOUS A ATTAQUÉ AVEC " + role + " PUISSANCE " + power +" !!!";
                redInfo->setText(QString::fromStdString(info));
            }
        }
    }

}
void ViewGui::displayWhoPlay(){
    QMessageBox msgBox;
    if(game->getCurrentPlayer()== BLUE && this->game->getState() == PLACEMENT){
        string s = "C'est au joueur BLEU de jouer";
        msgBox.information(this,"Qui dois jouer ?",QString::fromStdString(s));
        msgBox.setMinimumSize(200,200);

    } else if( game->getCurrentPlayer()== RED && this->game->getState() == PLACEMENT){
        string s = "C'est au joueur ROUGE de jouer";
        msgBox.information(this,"Qui dois jouer ?",QString::fromStdString(s));
        msgBox.setMinimumSize(200,200);
    }

}

void ViewGui::placeElement(Position pos,int nb, PLAYER actualPlayerButton){
    PIECE role;
    switch(nb){
    case 10 :
        role = MARECHAL;
        break;
    case 9:
        role = GENERAL;
        break;
    case 8:
        role = COLONEL;
        break;
    case 7:
        role = MAJOR;
        break;
    case 6:
        role = COMMANDANT;
        break;
    case 5:
        role = LIEUTENANT;
        break;
    case 4:
        role = SERGENT;
        break;
    case  3 :
        role = DEMINEUR;
        break;
    case 2:
        role = ECLAIREUR;
        break;
    case 1:
        role = ESPIONNE;
        break;
    case -1:
        role = DRAPEAU;
        break;
    case 11 :
        role = BOMBE;
        break;
    }
    GameElement elementToPlace(role,nb,actualPlayerButton);
    this->game->initializeBattleField(pos,actualPlayerButton,elementToPlace);
}

void ViewGui::initialiseGameFile(){
    QString file = QFileDialog::getOpenFileName(this,"Choose you file");
    fstream myFile(file.toStdString());
    if(!myFile){
        cout << "fichier introuvable" << endl;
        exit(1);
    }else{
        string data;
        vector<string> battleField {};
        while(myFile >> data)
            battleField.push_back(data);
        myFile.close();
        if(!game->goodFile(battleField)){
            cerr << "Vous n'avez pas la bonne configuration de fichier, veuillez relancer le programme avec le bon nombre de pieces" << endl;
            exit(1);
        }
        this->game->initializeBattelField(battleField);
    }
}

Position ViewGui::directionTs(DIRECTION dir){
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

    return direction;
}

bool ViewGui::conditionPosition(Position pos, Position toGo){
    int row = toGo.getX();
    int col = toGo.getY();
    if(col > 9 || row < 0 || row > 9 || col < 0 ){
        changeInfo("vous ne pouvez pas placer en dehors du champ de bataille");
        return false;
    }
    if(this->game->getSoldier(pos)->getRole() == DRAPEAU){
        changeInfo("vous ne pouvez pas deplacer votre drapeau choisissez de nouveau un soldat à bouger et une direction");
        return false;
    }

    if(this->game->getSoldier(pos)->getRole() == BOMBE){
        changeInfo("vous ne pouvez pas deplacer votre bombe choisisez de nouveau un soldat à bouger et une direction");
        return false;
    }
    if(this->game->getSoldier(toGo)->isWater()){
        changeInfo("vous ne pouvez pas deplacer sur de l'eau");
        return false;
    }
    if(this->game->getSoldier(toGo) != nullopt && !this->game->getSoldier(toGo)->isDecor() && this->game->getSoldier(toGo)->getColor() == this->game->getCurrentPlayer()){
        changeInfo("vous ne pouvez pas deplacer ici, il y a déjà l'un de vos pions");
        return false;
    }
    return true;
}
void ViewGui::setIcon( std::optional<GameElement>gameElement, QPushButton * soldier){
    if(gameElement->getColor()==RED){
        switch(gameElement->getRole().value()){
        case MARECHAL:
            soldier->setIcon(QIcon(":/ressources/stratego-miner-red.png"));
            break;
        case GENERAL:
            soldier->setIcon(QIcon(":/ressources/stratego-general-red.png"));
            break;
        case COLONEL:
            soldier->setIcon(QIcon(":/ressources/stratego-colonel-red.png"));
            break;
        case MAJOR:
            soldier->setIcon(QIcon(":/ressources/stratego-major-red.png"));
            break;
        case COMMANDANT:
            soldier->setIcon(QIcon(":/ressources/stratego-captain-red.png"));
            break;
        case LIEUTENANT:
            soldier->setIcon(QIcon(":/ressources/stratego-lieutenant-red.png"));
            break;
        case SERGENT:
            soldier->setIcon(QIcon(":/ressources/stratego-sergeant-red.png"));
            break;
        case DEMINEUR:
            soldier->setIcon(QIcon(":/ressources/stratego-miner-red.png"));
            break;
        case ECLAIREUR:
            soldier->setIcon(QIcon(":/ressources/stratego-scout-red.png"));
            break;
        case ESPIONNE:
            soldier->setIcon(QIcon(":/ressources/stratego-spy-red.png"));
            break;
        case DRAPEAU:
            soldier->setIcon(QIcon(":/ressources/stratego-red.png"));
            break;
        case BOMBE:
            soldier->setIcon(QIcon(":/ressources/stratego-bomb-red.png"));
            break;
        }
    } else {
        switch(gameElement->getRole().value()){
        case MARECHAL:
            soldier->setIcon(QIcon(":/ressources/stratego-miner.png"));
            break;
        case GENERAL:
            soldier->setIcon(QIcon(":/ressources/stratego-general.png"));
            break;
        case COLONEL:
            soldier->setIcon(QIcon(":/ressources/stratego-colonel.png"));
            break;
        case MAJOR:
            soldier->setIcon(QIcon(":/ressources/stratego-major.png"));
            break;
        case COMMANDANT:
            soldier->setIcon(QIcon(":/ressources/stratego-captain.png"));
            break;
        case LIEUTENANT:
            soldier->setIcon(QIcon(":/ressources/stratego-lieutenant.png"));
            break;
        case SERGENT:
            soldier->setIcon(QIcon(":/ressources/stratego-sergeant.png"));
            break;
        case DEMINEUR:
            soldier->setIcon(QIcon(":/ressources/stratego-miner.png"));
            break;
        case ECLAIREUR:
            soldier->setIcon(QIcon(":/ressources/stratego-scout.png"));
            break;
        case ESPIONNE:
            soldier->setIcon(QIcon(":/ressources/stratego-spy.png"));
            break;
        case DRAPEAU:
            soldier->setIcon(QIcon(":/ressources/stratego-blue.png"));
            break;
        case BOMBE:
            soldier->setIcon(QIcon(":/ressources/stratego-bomb.png"));
            break;


        }

    }
}

