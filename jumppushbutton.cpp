#include "jumppushbutton.h"
#include<qdebug.h>
#include<qpropertyanimation.h>
#include<QTimer>

JumpPushButton::JumpPushButton(QString normalImg,QString pressImg)
{
    normalImgPath=normalImg;
    pressImgPath=pressImg;
    QPixmap pixmap;
    //Judge whether it can be loaded
    bool ret =pixmap.load(normalImgPath);
    if(!ret){
        qDebug()<<normalImg<<"Image loading failed";
    }
    this->setFixedSize(pixmap.width(),pixmap.height());
    //set free style sheet
    this->setStyleSheet("QPushButton{border:0px}");
    this->setIcon(pixmap);
    this->setIconSize(QSize(pixmap.width(),pixmap.height()));
}

void JumpPushButton::jumpDown()
{
    QPropertyAnimation* animation1 = new QPropertyAnimation(this, "geometry");
    animation1->setDuration(200);
    animation1->setStartValue(QRect(this->x(), this->y(), this->width(), this->height()));
    animation1->setEndValue(QRect(this->x(), this->y()+10, this->width(), this->height()));
    //set smooth liner ease
    animation1->setEasingCurve(QEasingCurve::OutBounce);
    animation1->start();
}

void JumpPushButton::jumpUp()
{
    QPropertyAnimation* animation1 = new QPropertyAnimation(this, "geometry");
    animation1->setDuration(200);
    animation1->setStartValue(QRect(this->x(), this->y()+ 10, this->width(), this->height()));
    animation1->setEndValue(QRect(this->x(), this->y() , this->width(), this->height()));
    //set smooth liner ease
    animation1->setEasingCurve(QEasingCurve::OutBounce);
    animation1->start();
}

//change pic
void JumpPushButton::mousePressEvent(QMouseEvent*e)
{
    //选中路径不为空，显示选中图片
    if (pressImgPath != "") {
        QPixmap pixmap;
        bool ret = pixmap.load(pressImgPath);
        if (!ret) {
            qDebug() << pressImgPath << "Image loading failed ";
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

void JumpPushButton::mouseReleaseEvent(QMouseEvent*e)
{
    //选中路径不为空，显示选中图片
    if (this->pressImgPath != "") {
        QPixmap pixmap;
        bool ret = pixmap.load(normalImgPath);
        if (!ret) {
            qDebug() << normalImgPath << "Image loading failed ";
            return;
        }
        QTimer::singleShot(0, this, [=]() {
            //set fixed size
            this->setFixedSize(pixmap.width(), pixmap.height());
            //set free style sheet
            this->setStyleSheet("QPushButton{border:0px;}");
            this->setIcon(pixmap);
            this->setIconSize(QSize(pixmap.width(), pixmap.height()));
        });

    }
    return QPushButton::mouseReleaseEvent(e);
}









