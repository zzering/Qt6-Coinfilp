#pragma once

#include <QMainWindow>
#include"mycoin.h"
class PlayScence : public QMainWindow
{
	Q_OBJECT

public:
	//PlayScence(QWidget *parent);
	PlayScence(int levelNum);
	int levelIndex;//记录关卡num
	bool isWin;//胜利标志
	int gameArray[4][4]; //二维数组 关卡数据
	MyCoin* coinBtn[4][4]; //金币按钮数组

	~PlayScence();
	void paintEvent(QPaintEvent*);

signals:
	void chooseSceneBack();
};
