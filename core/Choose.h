//
// Created by Uniqu on 1/31/2021.
//

#ifndef CHESS_CHOOSE_H
#define CHESS_CHOOSE_H

#include <QObject>

class Choose: public QObject{
Q_OBJECT
private:
    int select;

public:
    explicit Choose(int index);
    void showMainWindow();

private:
};


#endif //CHESS_CHOOSE_H
