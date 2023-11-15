#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <vector>
#include <fstream>
#include <QTimer>
#include <QThread>    //Time Delay

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class Sleeper : public QThread // Time Delay
{
public:
    static void usleep(unsigned long usecs){QThread::usleep(usecs);}
    static void msleep(unsigned long msecs){QThread::msleep(msecs);}
    static void sleep(unsigned long secs){QThread::sleep(secs);}
};

//Sleeper::usleep(10);  microseconds
//Sleeper::msleep(10);  milliseconds
//Sleeper::sleep(10);   seconds

struct Card{

    int nValue = 0;
    std::string sValue{};
    std::string sSuit{};
    int index = 0;
    bool cardDealt = false;
};

struct Game{

    int playerCredits = 2000;
    int computerCredits = 2000;
    int playerHandValue = 0;
    int computerHandValue = 0;
    int currentBet = 0;
    int playerHandIDX = 0;
    int computerHandIDX = 0;
    bool gamestarted = false;
    bool playerTurn = true;
    bool bankjustlost = false;
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void createAdressVector();
    Card createNewCard(int suit, int value);
    void createNewDeck();
    void shuffleDeck();
    void resetDeckasNotDealt();
    Card dealCard();
    void on_actionNytt_Spel_triggered();
    void on_Button_50_clicked();
    void updateWindow();
    void clearHand();
    void on_Button_100_clicked();
    void on_Button_10_clicked();
    void on_Dra_Kort_button_clicked();
    std::string returnPictureAdress(int cardindex);
    void drawCards();
    void drawCardsComputer();
    int cardValue(std::vector<Card> playerHand);
    void calculateWinner();
    void checkIfBust();
    void resetValues();
    void resetWindowpics();
    void checkIfEndGame();
    void on_Stanna_button_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
