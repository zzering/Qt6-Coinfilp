#pragma once
#include <QMainWindow>
#include"playscence.h"

class ChooseLevelScene : public QMainWindow
{
	Q_OBJECT

public:
	ChooseLevelScene(QWidget* parent = Q_NULLPTR);
	//ChooseLevelScene(QWidget* parent);
	void paintEvent(QPaintEvent*);

	~ChooseLevelScene();
	PlayScence* pScence = Q_NULLPTR;

signals:
	void chooseSceneBack();

};
