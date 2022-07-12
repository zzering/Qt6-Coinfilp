#pragma once
#include <qpushbutton.h>
class MyPushButton : public QPushButton
{
	Q_OBJECT

public:
	MyPushButton(QString normalImg, QString pressImg = "");
	void jumpDown();
	void jumpUp();
	void mousePressEvent(QMouseEvent*e);
	void mouseReleaseEvent(QMouseEvent*e);
	QString normalImgPath;
	QString pressImgPath;
	~MyPushButton();
};
