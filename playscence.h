#pragma once

#include <QMainWindow>
#include"mycoin.h"
class PlayScence : public QMainWindow
{
	Q_OBJECT

public:
	//PlayScence(QWidget *parent);
	PlayScence(int levelNum);
	int levelIndex;//��¼�ؿ�num
	bool isWin;//ʤ����־
	int gameArray[4][4]; //��ά���� �ؿ�����
	MyCoin* coinBtn[4][4]; //��Ұ�ť����

	~PlayScence();
	void paintEvent(QPaintEvent*);

signals:
	void chooseSceneBack();
};
