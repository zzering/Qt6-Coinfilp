#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include<QTimer>


class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    MyCoin(QString btnImg);
    void changeFlag();
    int posX; //x坐标
    int posY; //y坐标
    int min = 1;
    int max = 8;
    bool flag; //正反标志
    QTimer *timer1;
    QTimer *timer2;
    bool isWin= false;//按钮的胜利标志
    bool isAnimation = false;//判断动画
    void mousePressEvent(QMouseEvent *e);
};

#endif // MYCOIN_H
