#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <chrono>
#include <thread>


std::vector<std::string> adresses;
std::vector<Card> theDeck;
std::vector<Card> playerHand;
std::vector<Card> computerHand;
Game currentGame;



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createAdressVector(){

    std::string filnamn("C:/QTprojects/Tjugo_ett/Text_Files/adresstopic.txt");
    std::ifstream filen(filnamn);

    while (!filen.fail()) {
        std::string ettOrd;
        filen >> ettOrd;
        if (!filen.fail())
            adresses.push_back(ettOrd);
    }
}

std::string MainWindow::returnPictureAdress(int cardindex){

    for (int i = 0; i < 52; i++){

        if( i == cardindex)
            return adresses[i];
    }
    return returnPictureAdress(cardindex);
}

void MainWindow::updateWindow(){
    ui->Computer_Credits->setNum(currentGame.computerCredits);
    ui->Player_Credits->setNum(currentGame.playerCredits);
    ui->Current_Bet->setNum(currentGame.currentBet);
    ui->Player_Card_Value->setNum(currentGame.playerHandValue);
    ui->Computer_Card_Value->setNum(currentGame.computerHandValue);
}

void MainWindow::clearHand()
{
playerHand.clear();
computerHand.clear();
}

void MainWindow::resetValues(){
    currentGame.currentBet = 0;
    currentGame.playerHandValue = 0;
    currentGame.computerHandValue = 0;
    currentGame.computerHandIDX = 0;
    currentGame.playerHandIDX = 0;
    shuffleDeck();
    resetDeckasNotDealt();
}

void MainWindow::resetWindowpics()
{

    ui->Player_Card_1->clear();
    ui->Player_Card_2->clear();
    ui->Player_Card_3->clear();
    ui->Player_Card_4->clear();
    ui->Player_Card_5->clear();
    ui->Player_Card_6->clear();
    ui->Player_Card_7->clear();
    ui->Player_Card_8->clear();
    ui->Player_Card_9->clear();
    ui->Player_Card_10->clear();
    ui->Player_Card_11->clear();
    ui->Comp_Card_1->clear();
    ui->Comp_Card_2->clear();
    ui->Comp_Card_3->clear();
    ui->Comp_Card_4->clear();
    ui->Comp_Card_5->clear();
    ui->Comp_Card_6->clear();
    ui->Comp_Card_7->clear();
    ui->Comp_Card_8->clear();
    ui->Comp_Card_9->clear();
    ui->Comp_Card_10->clear();
    ui->Comp_Card_11->clear();
}

void MainWindow::checkIfEndGame()
{
    if(currentGame.computerCredits <=0){
    ui->Text_Out->setText("Banken har inga pengar kvar, du vann! \n Starta nytt spel i menyn.");
        currentGame.gamestarted = false;
    }
    if(currentGame.playerCredits <= 0){
        ui->Text_Out->setText("Du har inga pengar kvar, du förlorade! \n Starta nytt spel i menyn.");
        currentGame.gamestarted = false;
    }
}

void MainWindow::resetDeckasNotDealt()
{
    for(auto it = theDeck.begin(); it != theDeck.end(); it++){
        it->cardDealt = false;
    }
}


void MainWindow::checkIfBust(){

    if (currentGame.playerHandValue > 21) {
        ui->Text_Out->setText("Du gick over! \n Satsa för att starta en ny omgång");
        currentGame.computerCredits += currentGame.currentBet*2;
        currentGame.playerCredits -= currentGame.currentBet;
        checkIfEndGame();
        resetValues();
        clearHand();
        return;
    }
    if (currentGame.computerHandValue > 21) {
        ui->Text_Out->setText("Banken gick över! \n Tryck på Stanna för att starta en ny omgång");
        currentGame.computerCredits -= currentGame.currentBet;
        currentGame.playerCredits += currentGame.currentBet*2;
        checkIfEndGame();
        resetValues();
        currentGame.bankjustlost = true;
        currentGame.playerTurn = true;
        clearHand();
        return;
    }
}

void MainWindow::calculateWinner() {

    if (currentGame.playerHandValue > currentGame.computerHandValue) {
        ui->Text_Out->setText("Du vann! \n Tryck på Stanna för att starta en ny omgång");
        currentGame.computerCredits -= currentGame.currentBet;
        currentGame.playerCredits += currentGame.currentBet*2;
        checkIfEndGame();
        resetValues();
        currentGame.bankjustlost = true;
        currentGame.playerTurn = true;
        clearHand();
        return;
    }
    if (currentGame.playerHandValue < currentGame.computerHandValue) {
        ui->Text_Out->setText("Du förlorade! \n Tryck på Stanna för att starta en ny omgång");
        currentGame.computerCredits += currentGame.currentBet*2;
        currentGame.playerCredits -= currentGame.currentBet;
        checkIfEndGame();
        resetValues();
        currentGame.bankjustlost = true;
        currentGame.playerTurn = true;
        clearHand();
        return;
    }
    if (currentGame.playerHandValue == currentGame.computerHandValue) {
        ui->Text_Out->setText("Oavgjort! \n Tryck på Stanna för att starta en ny omgång");
        currentGame.playerCredits += currentGame.currentBet;
        checkIfEndGame();
        resetValues();
        currentGame.bankjustlost = true;
        currentGame.playerTurn = true;
        clearHand();
        return;
    }
}

void MainWindow::drawCards(){

    QString qstring = returnPictureAdress(playerHand[currentGame.playerHandIDX-1].index).data();
    QPixmap picmap(qstring);
    if(currentGame.playerHandIDX-1 == 0)
    ui->Player_Card_1->setPixmap(picmap);
    if(currentGame.playerHandIDX-1 == 1)
    ui->Player_Card_2->setPixmap(picmap);
    if(currentGame.playerHandIDX-1 == 2)
    ui->Player_Card_3->setPixmap(picmap);
    if(currentGame.playerHandIDX-1 == 3)
    ui->Player_Card_4->setPixmap(picmap);
    if(currentGame.playerHandIDX-1 == 4)
    ui->Player_Card_5->setPixmap(picmap);
    if(currentGame.playerHandIDX-1 == 5)
    ui->Player_Card_6->setPixmap(picmap);
    if(currentGame.playerHandIDX-1 == 6)
    ui->Player_Card_7->setPixmap(picmap);
    if(currentGame.playerHandIDX-1 == 7)
    ui->Player_Card_8->setPixmap(picmap);
    if(currentGame.playerHandIDX-1 == 8)
    ui->Player_Card_9->setPixmap(picmap);
    if(currentGame.playerHandIDX-1 == 9)
    ui->Player_Card_10->setPixmap(picmap);
    if(currentGame.playerHandIDX-1 == 10)
    ui->Player_Card_11->setPixmap(picmap);
}

void MainWindow::drawCardsComputer(){

    QString qstring = returnPictureAdress(computerHand[currentGame.computerHandIDX-1].index).data();
    QPixmap picmap(qstring);
    if(currentGame.computerHandIDX-1 == 0)
    ui->Comp_Card_1->setPixmap(picmap);
    if(currentGame.computerHandIDX-1 == 1)
    ui->Comp_Card_2->setPixmap(picmap);
    if(currentGame.computerHandIDX-1 == 2)
    ui->Comp_Card_3->setPixmap(picmap);
    if(currentGame.computerHandIDX-1 == 3)
    ui->Comp_Card_4->setPixmap(picmap);
    if(currentGame.computerHandIDX-1 == 4)
    ui->Comp_Card_5->setPixmap(picmap);
    if(currentGame.computerHandIDX-1 == 5)
    ui->Comp_Card_6->setPixmap(picmap);
    if(currentGame.computerHandIDX-1 == 6)
    ui->Comp_Card_7->setPixmap(picmap);
    if(currentGame.computerHandIDX-1 == 7)
    ui->Comp_Card_8->setPixmap(picmap);
    if(currentGame.computerHandIDX-1 == 8)
    ui->Comp_Card_9->setPixmap(picmap);
    if(currentGame.computerHandIDX-1 == 9)
    ui->Comp_Card_10->setPixmap(picmap);
    if(currentGame.computerHandIDX-1 == 10)
    ui->Comp_Card_11->setPixmap(picmap);
}

int MainWindow::cardValue(std::vector<Card> hand) {

    int score = 0;
    int amountofAces = 0;

    for (auto it = hand.begin(); it != hand.end(); it++) {

        if (it->nValue == 1) {
            amountofAces += 1;
        }
        if (it->nValue == 11 || it->nValue == 12 || it->nValue == 13) {
            score += 10;
            continue;
        }

        score += it->nValue;
    }
    if (amountofAces >= 1)
    {
        if (score <= 11)
            score += 10;
    }

    return score;
}

void MainWindow::shuffleDeck(){

    std::random_shuffle(theDeck.begin(), theDeck.end());
}


Card MainWindow::dealCard(){

    for(int i = 0; i < 52; i++){

        if(!theDeck[i].cardDealt){
            theDeck[i].cardDealt = true;
            return theDeck[i];
        }
    }
    return dealCard();
}

Card MainWindow::createNewCard(int suit, int value){

    std::string colours[4] = {"Hearts", "Diamonds", "Clubs", "Spades"};
    std::string values[13] = { "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };
    Card newCard;

    newCard.nValue = value+1;
    newCard.sSuit = colours[suit];
    newCard.sValue = values[value];

    return newCard;
}

void MainWindow::createNewDeck(){
int currentIndex = 0;

    for (int colour = 0; colour < 4; colour++)
    {
        for (int value = 0; value < 13; value++)
        {
            theDeck.push_back(createNewCard(colour, value));
            theDeck[currentIndex].index = currentIndex;
            currentIndex +=1;
        }
    }
}

void MainWindow::on_actionNytt_Spel_triggered()
{
    currentGame.gamestarted = true;
    resetValues();
    currentGame.playerCredits = 2000;
    currentGame.computerCredits = 2000;
    createNewDeck();
    shuffleDeck();
    createAdressVector();
    resetWindowpics();
    updateWindow();
    ui->Text_Out->setText("Satsa hur mycket du vill och tryck \n sedan på Dra Kort");
}

void MainWindow::on_Button_50_clicked()
{
    if(!currentGame.gamestarted)
        return;
    if(currentGame.playerCredits >= 50 && currentGame.playerTurn){
        currentGame.playerCredits -= 50;
        currentGame.currentBet += 50;
        resetWindowpics();
        updateWindow();
    }
    else return;
}
void MainWindow::on_Button_100_clicked()
{
    if(!currentGame.gamestarted)
        return;
    if(currentGame.playerCredits >= 100 && currentGame.playerTurn){
        currentGame.playerCredits -=100;
        currentGame.currentBet +=100;
        resetWindowpics();
        updateWindow();
    }
        else return;
}
void MainWindow::on_Button_10_clicked()
{
    if(!currentGame.gamestarted)
        return;
    if(currentGame.playerCredits >= 10 && currentGame.playerTurn){
        currentGame.playerCredits -=10;
        currentGame.currentBet +=10;
        resetWindowpics();
        updateWindow();
    }
        else return;
}


void MainWindow::on_Dra_Kort_button_clicked()
{
    if(!currentGame.gamestarted)
        return;
    if(currentGame.playerTurn){
        if(currentGame.currentBet == 0){
            ui->Text_Out->setText("Du måste satsa något innan en \n ny omgång kan startas.");
            return;
        }
        currentGame.bankjustlost = false;
        playerHand.push_back(dealCard());
        currentGame.playerHandIDX +=1;
        ui->Text_Out->setText("När du är redo att stanna och låta banken spela \n tryck på knappen Stanna.");
        currentGame.playerHandValue = cardValue(playerHand);
        updateWindow();
        drawCards();
        checkIfBust();
    }
}


void MainWindow::on_Stanna_button_clicked()
{
    if(!currentGame.gamestarted)
        return;
    if(currentGame.bankjustlost){
    ui->Text_Out->setText("Satsa och tryck Dra Kort \n för att starta en ny omgång");
    updateWindow();
    resetWindowpics();
    return;
    }

    if(currentGame.playerTurn){
        currentGame.playerTurn = false;
        ui->Text_Out->setText("Banken ska spela nu. Tryck på Stanna knappen \n för att spela en omgång åt banken");
    }
    else{
        computerHand.push_back(dealCard());
        currentGame.computerHandIDX +=1;
        currentGame.computerHandValue = cardValue(computerHand);
        updateWindow();
        drawCardsComputer();
        checkIfBust();
        if(currentGame.computerHandValue >= 17){
            calculateWinner();
            currentGame.playerTurn = true;
        }
    }

}

