#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include"mycoin.h"

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    PlayScene(int levelnum);
    int levelIndex;//Record level's num
    bool isWin;//胜利标志
    void paintEvent(QPaintEvent*);
    int gameArray[4][4];
    MyCoin* coinBtn[4][4]; //金币按钮数组
signals:
    void chooseSceneBack();
};

#endif // PLAYSCENE_H
