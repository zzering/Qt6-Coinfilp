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
	//创建菜单栏
	QMenuBar* bar = this->menuBar();
	this->setMenuBar(bar);
	//创建开始菜单
	QMenu* startMenu = bar->addMenu("开始");
	//创建按钮菜单项
	QAction* quitAction = startMenu->addAction("退出");
	//点击退出 退出游戏
	connect(quitAction, &QAction::triggered, [=]() {
		this->close(); });
	//翻金币音效
	QSound* flipSound = new QSound(":/res/ConFlipSound.wav", this);
	//胜利按钮音效
	QSound* winSound = new QSound(":/res/LevelWinSound.wav", this);
	//backBtn
	MyPushButton* backBtn = new MyPushButton(":/res/BackButton.png", ":/res/BackButtonSelected.png");
	backBtn->setParent(this);
	backBtn->move(this->width() - backBtn->width(), this->height() - backBtn->height());
	connect(backBtn, &MyPushButton::clicked, [=]() {
		QTimer::singleShot(250, this, [=]() {
			//触发自定义信号，关闭自身，该信号写到 signals下做声明
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

	//将胜利的图片提前创建好，如果胜利触发了，将图片弹下来即可
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
			qreal width = pix.width();//获得以前图片的宽和高
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
			coin->flag = this->gameArray[i][j];//1正面 0反面
			//翻转其上下左右1
			coinBtn[i][j] = coin;
			//点击金币 翻转
			connect(coin, &MyCoin::clicked, [=]() {
				flipSound->play();
				//点击按钮 将所有按钮禁用
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 4; j++) {
						this->coinBtn[i][j]->isWin = true;
					}
				}
				coin->changeFlag();
				//数组内部记录的标志同步修改//////
				this->gameArray[i][j] = gameArray[i][j] == 0 ? 1 : 0;
				//翻转其上下左右2
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
					//翻完周围金币后 将所有金币解开禁用
					for (int i = 0; i < 4; i++) {
						for (int j = 0; j < 4; j++) {
							this->coinBtn[i][j]->isWin = false;
						}
					}
					//判断是否胜利
					this->isWin = true;
					for (int i = 0; i < 4; i++) {
						for (int j = 0; j < 4; j++) {
							//有一个反面就未成功
							if (coinBtn[i][j]->flag == false) {
								this->isWin = false;
								break;
							}
						}
					}
					//将所有按钮的胜利标志改为true 再次点击对应按钮就return (void MyCoin::mousePressEvent(QMouseEvent* e))
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
	//加载背景
	QPainter painter(this);
	QPixmap pix;
	pix.load(":/res/PlayLevelSceneBg.png");
	painter.drawPixmap(0, 0, this->width(), this->height(), pix);
	//加载标题
	pix.load(":/res/Title.png");
	pix = pix.scaled(pix.width() * 0.6, pix.height() * 0.6);
	painter.drawPixmap(10, 30, pix);

}



PlayScence::~PlayScence()
{
}
