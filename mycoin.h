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
	int posX; //x����
	int posY; //y����
	int min = 1;
	int max = 8;
	bool flag; //������־
	bool isWin=false;//��ť��ʤ����־
	bool isAnimation = false;//�ж϶���
	void mousePressEvent(QMouseEvent* e);
};
