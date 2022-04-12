#include "mycoin.h"
#include<QPixmap>
#include<QDebug>

MyCoin::MyCoin(QString btnImg)
{
    QPixmap pixmap;
    bool ret = pixmap.load(btnImg);
    if(!ret){
        qDebug() << btnImg << "Image loading failed";
    }

    this->setFixedSize( pixmap.width(), pixmap.height() );
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pixmap);
    this->setIconSize(QSize(pixmap.width(),pixmap.height()));
    //初始化定时器对象
    timer1 = new QTimer(this);
    timer2 = new QTimer(this);
    connect(timer1, &QTimer::timeout, [=]() {
        QPixmap pix;
        QString str = QString(":/res/Coin000%1").arg(this->min++);
        pix.load(str);
        this->setFixedSize(pix.width(), pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(), pix.height()));
        //如果翻完了 将min=1
        if (this->min > this->max) {
            this->min = 1;
            isAnimation = false;//end animation
            timer1->stop();
        }
    });
    //monitor the singal of back->front then flip the coin
    connect(timer2, &QTimer::timeout, [=]() {
        QPixmap pix;
        QString str = QString(":/res/Coin000%1").arg(this->max--);
        pix.load(str);
        this->setFixedSize(pix.width(), pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(), pix.height()));
        //如果翻完了 将max=8
        if (this->max < this->min) {
            this->max = 8;
            isAnimation = false;//end animation
            timer2->stop();
        }
    });

}

void MyCoin::changeFlag()
{
    //如果是正面，执行下列代码
    if (this->flag) {
        timer1->start(30);
        isAnimation = true;//start animation
        this->flag = false;
    }
    else {
        timer2->start(30);
        isAnimation = true;//start animation
        this->flag = true;
    }
}

//monitor the mouse event
//如果快速点击，会在金币还没有执行一个完整动作之后 ，又继续开始新的动画，我们应该在金币做动画期间，禁止再次点击，并在完成动画后，开启点击
void MyCoin::mousePressEvent(QMouseEvent* e)
{
    //if there are annimation is being playing then stop other mousevents
    if (this->isAnimation||this->isWin) {
        return;
    }
    else {
        QPushButton::mousePressEvent(e);//can be skipped
    }
}



