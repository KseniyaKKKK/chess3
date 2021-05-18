#ifndef MENU_H
#define MENU_H
#include <QPushButton>
#include <QWidget>

class Menu : public QWidget
{
public:
    QPushButton *quitButton = new QPushButton("White", this);
    QPushButton *quitButton2 = new QPushButton("Black", this);
    Menu(QWidget *perent = 0);
};

#endif // MENU_H
