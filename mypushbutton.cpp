#include "mypushbutton.h"
#include<qdebug.h>
#include<qpropertyanimation.h>

MyPushButton::MyPushButton(QString normalImg, QString pressImg)
{
	normalImgPath = normalImg;
	pressImgPath = pressImg;
	QPixmap pixmap;
	bool ret = pixmap.load(normalImgPath);
	if (!ret) {
		qDebug() << normalImg << "图片加载失败 ";
		return;
	}
	//set fixed size
	this->setFixedSize(pixmap.width(), pixmap.height());
	//set free style sheet
	this->setStyleSheet("QPushButton{border:0px;}");
	this->setIcon(pixmap);
	this->setIconSize(QSize(pixmap.width(), pixmap.height()));
}


void MyPushButton::jumpDown()
{
	QPropertyAnimation* animation1 = new QPropertyAnimation(this, "geometry");
	animation1->setDuration(200);
	animation1->setStartValue(QRect(this->x(), this->y(), this->width(), this->height()));
	animation1->setEndValue(QRect(this->x(), this->y()+10, this->width(), this->height()));
	//set smooth liner    ease
	animation1->setEasingCurve(QEasingCurve::OutBounce);
	animation1->start();
}

void MyPushButton::jumpUp()
{
	QPropertyAnimation* animation1 = new QPropertyAnimation(this, "geometry");
	animation1->setDuration(200);
	animation1->setStartValue(QRect(this->x(), this->y()+ 10, this->width(), this->height()));
	animation1->setEndValue(QRect(this->x(), this->y() , this->width(), this->height()));
	//set smooth liner    ease
	animation1->setEasingCurve(QEasingCurve::OutBounce);
	animation1->start();
}

void MyPushButton::mousePressEvent(QMouseEvent*e)
{
	//选中路径不为空，显示选中图片
	if (pressImgPath != "") {
		QPixmap pixmap;
		bool ret = pixmap.load(pressImgPath);
		if (!ret) {
			qDebug() << pressImgPath << "图片加载失败 ";
			exit(-1);
		}
		//set fixed size
		this->setFixedSize(pixmap.width(), pixmap.height());
		//set free style sheet
		this->setStyleSheet("QPushButton{border:0px;}");
		this->setIcon(pixmap);
		this->setIconSize(QSize(pixmap.width(), pixmap.height()));
	}
	return QPushButton::mousePressEvent(e);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent*e)
{
	//选中路径不为空，显示选中图片
	if (this->pressImgPath != "") {
		QPixmap pixmap;
		bool ret = pixmap.load(normalImgPath);
		if (!ret) {
			qDebug() << normalImgPath << "图片加载失败 ";
			return;
		}
		//set fixed size
		this->setFixedSize(pixmap.width(), pixmap.height());
		//set free style sheet
		this->setStyleSheet("QPushButton{border:0px;}");
		this->setIcon(pixmap);
		this->setIconSize(QSize(pixmap.width(), pixmap.height()));
	}
	return QPushButton::mouseReleaseEvent(e);
}


MyPushButton::~MyPushButton()
{
}
