#pragma once
#include <QPushButton>
#include<qtimer.h>

class MyCoin : public QPushButton
{
	Q_OBJECT

public:
	//MyCoin(QWidget *parent);
	~MyCoin();
	MyCoin(QString btnImg);
	void changeFlag();

	QTimer* timer1;
	QTimer *timer2;
	int posX; //x坐标
	int posY; //y坐标
	int min = 1;
	int max = 8;
	bool flag; //正反标志
	bool isWin=false;//按钮的胜利标志
	bool isAnimation = false;//判断动画
	void mousePressEvent(QMouseEvent* e);
};
