#include "playscence.h"
#include<Qmenu>
#include<QmenuBar>
#include<qpainter.h>
#include"mypushbutton.h"
#include<qtimer.h>
#include <QLabel>
#include<qpixmap.h>
#include"mycoin.h"
#include"dataconfig.h"
#include<QPropertyAnimation>
#include<qsound.h>

#pragma execution_character_set("utf-8")

//PlayScence::PlayScence(QWidget *parent)
//	: QMainWindow(parent)
//{
//}

PlayScence::PlayScence(int levelNum)
{
	this->levelIndex = levelNum;
	//initialnize game scence
	this->setFixedSize(400, 700);
	this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
	this->setWindowTitle("Coinflip");
	//�����˵���
	QMenuBar* bar = this->menuBar();
	this->setMenuBar(bar);
	//������ʼ�˵�
	QMenu* startMenu = bar->addMenu("��ʼ");
	//������ť�˵���
	QAction* quitAction = startMenu->addAction("�˳�");
	//����˳� �˳���Ϸ
	connect(quitAction, &QAction::triggered, [=]() {
		this->close(); });
	//�������Ч
	QSound* flipSound = new QSound(":/res/ConFlipSound.wav", this);
	//ʤ����ť��Ч
	QSound* winSound = new QSound(":/res/LevelWinSound.wav", this);
	//backBtn
	MyPushButton* backBtn = new MyPushButton(":/res/BackButton.png", ":/res/BackButtonSelected.png");
	backBtn->setParent(this);
	backBtn->move(this->width() - backBtn->width(), this->height() - backBtn->height());
	connect(backBtn, &MyPushButton::clicked, [=]() {
		QTimer::singleShot(250, this, [=]() {
			//�����Զ����źţ��ر��������ź�д�� signals��������
			emit this->chooseSceneBack();
			});
		});

	//show current level
	QLabel* label = new QLabel;
	QFont font;
	font.setFamily("Microsoft YaHei");
	font.setPointSize(20);
	label->setFont(font);
	label->setParent(this);
	QString str = QString("Level:%1").arg(this->levelIndex);
	label->setText(str);
	label->setGeometry(20, this->height() - 50, 160, 50);

	//import data
	dataConfig config;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			this->gameArray[i][j] = config.mData[this->levelIndex][i][j];
		}
	}

	//��ʤ����ͼƬ��ǰ�����ã����ʤ�������ˣ���ͼƬ����������
	QLabel* winLabel = new QLabel;
	QPixmap tmpPix;
	tmpPix.load(":/res/LevelCompletedDialogBg.png");
	winLabel->setGeometry(0, 0, tmpPix.width(), tmpPix.height());
	winLabel->setPixmap(tmpPix);
	winLabel->setParent(this);
	winLabel->move((this->width() - tmpPix.width()) * 0.5, -tmpPix.height());

	//show coin background
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			QPixmap pix = QPixmap(":/res/BoardNode.png");
			qreal width = pix.width();//�����ǰͼƬ�Ŀ�͸�
			qreal height = pix.height();
			pix = pix.scaled(width * 1.5, height * 1.5, Qt::KeepAspectRatio);
			QLabel* label = new QLabel;
			label->setGeometry(0, 0, pix.width(), pix.height());
			label->setPixmap(pix);
			label->setParent(this);
			label->move(50 + i * 75, 200 + j * 75);
			//creat coin
			QString str;
			if (this->gameArray[i][j] == 1) {
				str = ":/res/Coin0001.png";
			}
			else {
				str = ":/res/Coin0008.png";
			}
			MyCoin* coin = new MyCoin(str);
			coin->setParent(this);
			coin->move(65 + i * 75, 215 + j * 75);
			coin->posX = i;
			coin->posY = j;
			coin->flag = this->gameArray[i][j];//1���� 0����
			//��ת����������1
			coinBtn[i][j] = coin;
			//������ ��ת
			connect(coin, &MyCoin::clicked, [=]() {
				flipSound->play();
				//�����ť �����а�ť����
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 4; j++) {
						this->coinBtn[i][j]->isWin = true;
					}
				}
				coin->changeFlag();
				//�����ڲ���¼�ı�־ͬ���޸�//////
				this->gameArray[i][j] = gameArray[i][j] == 0 ? 1 : 0;
				//��ת����������2
				QTimer::singleShot(200, this, [=]() {
					if (coin->posX + 1 <= 3) {
						coinBtn[coin->posX + 1][coin->posY]->changeFlag();
						this->gameArray[coin->posX + 1][coin->posY] = this->gameArray[coin->posX + 1][coin->posY] == 0 ? 1 : 0;
					}
					if (coin->posX - 1 >= 0) {
						coinBtn[coin->posX - 1][coin->posY]->changeFlag();
						this->gameArray[coin->posX - 1][coin->posY] = this->gameArray[coin->posX - 1][coin->posY] == 0 ? 1 : 0;
					}
					if (coin->posY + 1 <= 3) {  
						coinBtn[coin->posX][coin->posY + 1]->changeFlag();
						this->gameArray[coin->posX][coin->posY + 1] = this->gameArray[coin->posX + 1][coin->posY] == 0 ? 1 : 0;
					}
					if (coin->posY - 1 >= 0) {
						coinBtn[coin->posX][coin->posY - 1]->changeFlag();
						this->gameArray[coin->posX][coin->posY - 1] = this->gameArray[coin->posX + 1][coin->posY] == 0 ? 1 : 0;
					}
					//������Χ��Һ� �����н�ҽ⿪����
					for (int i = 0; i < 4; i++) {
						for (int j = 0; j < 4; j++) {
							this->coinBtn[i][j]->isWin = false;
						}
					}
					//�ж��Ƿ�ʤ��
					this->isWin = true;
					for (int i = 0; i < 4; i++) {
						for (int j = 0; j < 4; j++) {
							//��һ�������δ�ɹ�
							if (coinBtn[i][j]->flag == false) {
								this->isWin = false;
								break;
							}
						}
					}
					//�����а�ť��ʤ����־��Ϊtrue �ٴε����Ӧ��ť��return (void MyCoin::mousePressEvent(QMouseEvent* e))
					if (this->isWin == true) {
						winSound->play();
						for (int i = 0; i < 4; i++) {
							for (int j = 0; j < 4; j++) {
								coinBtn[i][j]->isWin = true;
							}
						}
						QPropertyAnimation* animation = new QPropertyAnimation(winLabel, "geometry");
						animation->setDuration(1000);
						animation->setStartValue(QRect(winLabel->x(), winLabel->y(), winLabel->width(), winLabel->height()));
						animation->setEndValue(QRect(winLabel->x(), winLabel->y() + 170, winLabel->width(), winLabel->height()));
						animation->setEasingCurve(QEasingCurve::OutBounce);
						animation->start();
					}
					});
				});
		}
	}
}

void PlayScence::paintEvent(QPaintEvent*)
{
	//���ر���
	QPainter painter(this);
	QPixmap pix;
	pix.load(":/res/PlayLevelSceneBg.png");
	painter.drawPixmap(0, 0, this->width(), this->height(), pix);
	//���ر���
	pix.load(":/res/Title.png");
	pix = pix.scaled(pix.width() * 0.6, pix.height() * 0.6);
	painter.drawPixmap(10, 30, pix);

}



PlayScence::~PlayScence()
{
}
