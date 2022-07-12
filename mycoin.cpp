#include "mycoin.h"
#include<qdebug.h>	
MyCoin::MyCoin(QString btnImg)
{
	QPixmap pix;
	bool ret = pix.load(btnImg);
	if (!ret) {
		QString str = QString("ͼƬ%1����ʧ��").arg(btnImg);
		qDebug() << str;
		return;
	}
	this->setFixedSize(pix.width(), pix.height());
	this->setStyleSheet("QPushButton{border:0px;}");
	this->setIcon(pix);
	this->setIconSize(QSize(pix.width(), pix.height()));
	//��ʼ����ʱ������
	timer1 = new QTimer(this);
	timer2 = new QTimer(this);
	//monitor the singal of front->back  then flip the coin
	connect(timer1, &QTimer::timeout, [=]() {
		QPixmap pix;
		QString str = QString(":/res/Coin000%1").arg(this->min++);
		pix.load(str);
		this->setFixedSize(pix.width(), pix.height());
		this->setStyleSheet("QPushButton{border:0px;}");
		this->setIcon(pix);
		this->setIconSize(QSize(pix.width(), pix.height()));
		//��������� ��min=1
		if (this->min > this->max) {
			this->min = 1;
			isAnimation = false;//end animation
			timer1->stop();
		}
		});
	//monitor the singal of back->front  then flip the coin
	connect(timer2, &QTimer::timeout, [=]() {
		QPixmap pix;
		QString str = QString(":/res/Coin000%1").arg(this->max--);
		pix.load(str);
		this->setFixedSize(pix.width(), pix.height());
		this->setStyleSheet("QPushButton{border:0px;}");
		this->setIcon(pix);
		this->setIconSize(QSize(pix.width(), pix.height()));
		//��������� ��max=8
		if (this->max < this->min) {
			this->max = 8;
			isAnimation = false;//end animation
			timer2->stop();
		}
		});
}

//monitor the mouse event 
//������ٵ�������ڽ�һ�û��ִ��һ����������֮�� ���ּ�����ʼ�µĶ���������Ӧ���ڽ���������ڼ䣬��ֹ�ٴε����������ɶ����󣬿������
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


//����
void MyCoin::changeFlag()
{
	//��������棬ִ�����д���
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


MyCoin::~MyCoin()
{
}
