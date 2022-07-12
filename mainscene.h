#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_mainscene.h"
#include"chooselevelscene.h"

class MainScene : public QMainWindow
{
	Q_OBJECT

public:
	MainScene(QWidget* parent = Q_NULLPTR);
	void paintEvent(QPaintEvent*);
	ChooseLevelScene* chooseScene = NULL;


private:
	Ui::MainSceneClass ui;
};
