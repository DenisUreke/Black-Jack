ifndef CARDS_H
#define CARDS_H

#include <QWidget>

namespace Ui {
class Cards;
}

class Cards : public QWidget
{
    Q_OBJECT

public:

    int nValue;
    std::string sSuit{};
    std::string sValue{};

    void fillDeckWithCards();
    void createCard(int suit, int value);

    explicit Cards(QWidget *parent = nullptr);
    ~Cards();

private:
    Ui::Cards *ui;
};

#endif // CARDS_H
