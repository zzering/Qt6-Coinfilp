#include "mainscene.h"
#include<qpainter.h>
#include<qpixmap.h>
#include"mypushbutton.h"
#include<qtimer.h>
////#include<QSound>

MainScene::MainScene(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	this->setFixedSize(400, 700);
	this->setWindowIcon(QPixmap(":/res/ds.png"));
	this->setWindowTitle("CoinFlip");
	connect(ui.actionQuit, &QAction::triggered, [=]() {
		this->close();
		});
	//sound
	////QSound* startSound = new QSound(":/res/TapButtonSound.wav", this);

	//creat diy button
	MyPushButton* startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");
	startBtn->setParent(this);
	startBtn->move(this->width() * 0.5 - startBtn->width() * 0.5, this->height() * 0.8);
	chooseScene = new ChooseLevelScene;

	//monitor the backbutton of choose level scence
	connect(chooseScene, &ChooseLevelScene::chooseSceneBack, this, [=]() {//delete this?/////////////ok
		//设置this场景位置
		this->setGeometry(chooseScene->geometry());
		chooseScene->hide();//hide the scence of chooselevel
		this->show();//reshow the mainscence
		});
	connect(startBtn, &MyPushButton::clicked, [=]() {
		//sound
		////startSound->play();
		//startSound->setLoops(-1);//无限循环	
		startBtn->jumpDown();
		startBtn->jumpUp();
		QTimer::singleShot(250, this, [=]() {
			//设置choosescence场景位置
			chooseScene->setGeometry(this->geometry());
			this->hide();
			chooseScene->show();
			});
		});
}
void MainScene::paintEvent(QPaintEvent*)
{
	QPainter painter(this);
	QPixmap pix;
	pix.load(":/res/PlayLevelSceneBg.png");
	//拉伸到当前长宽
	painter.drawPixmap(0, 0, this->width(), this->height(), pix);
	//title of coinflip
	pix.load(":/res/Title.png");
	pix = pix.scaled(pix.width() * 0.6, pix.height() * 0.6);
	painter.drawPixmap(10, 30, pix);//, width(), pix, height(), pix);
}