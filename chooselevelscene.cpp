#include"chooselevelscene.h"
#include<qmenubar.h>
#include<QPixmap>
#include<QPainter>
#include<QTimer>
#include"mypushbutton.h"
#include <QLabel>
#include<qdebug.h>
#include<QSound>
#pragma execution_character_set("utf-8")

ChooseLevelScene::ChooseLevelScene(QWidget* parent)
	: QMainWindow(parent)
{
	//设置窗口固定大小
	this->setFixedSize(400, 700);
	//设置图标
	this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
	//设置标题
	this->setWindowTitle("选择关卡");
	//创建菜单栏
	QMenuBar* bar = this->menuBar();
	this->setMenuBar(bar);
	//创建开始菜单
	QMenu* startMenu = bar->addMenu("开始");
	//创建按钮菜单项
	QAction* quitAction = startMenu->addAction("退出  " );
	//点击退出 退出游戏
	connect(quitAction, &QAction::triggered, [=]() {
		this->close(); });
	QSound* chooseSound = new QSound(":/res/TapButtonSound.wav", this);
	QSound* backSound = new QSound(":/res/BackButtonSound.wav", this);
	//backBtn
	MyPushButton* backBtn = new MyPushButton(":/res/BackButton.png", ":/res/BackButtonSelected.png");
	backBtn->setParent(this);
	backBtn->move(this->width() - backBtn->width(), this->height() - backBtn->height());
	connect(backBtn, &MyPushButton::clicked, [=]() {
		////backSound->play();
		QTimer::singleShot(250, this, [=]() {
			//触发自定义信号，关闭自身，该信号写到 signals下做声明
			emit this->chooseSceneBack();
			});
		});
	//creat choose level btn
	for (int i = 0; i < 20; i++) {
		MyPushButton* menuBtn = new MyPushButton(":/res/LevelIcon.png");
		menuBtn->setParent(this);
		menuBtn->move(40 + i % 4 * 90, 150 + i / 4 * 90);
		//monitor every level btn event
		connect(menuBtn, &MyPushButton::clicked, [=]() {
			////chooseSound->play();
			//QString str = QString("选择的是第%1关").arg(i + 1);
			//qDebug() << str;
			this->hide();	//hide level scence
			pScence = new PlayScence(i + 1);//creat game scence
			pScence->setGeometry(this->geometry());
			pScence->show();
			//monitor back btn
			connect(pScence, &PlayScence::chooseSceneBack, [=]() {
				this->setGeometry(pScence->geometry());
				////backSound->play();
				this->show();
				delete pScence;
				pScence = Q_NULLPTR;
				});
			});

		//按钮上显示的文字
		QLabel* label = new QLabel;
		label->setParent(this);
		label->setFixedSize(menuBtn->width(), menuBtn->height());
		label->setText(QString::number(i + 1));
		QFont font;
		font.setFamily("Microsoft YaHei");
		font.setPointSize(14);
		label->setFont(font);
		label->setAlignment(Qt::AlignCenter);//equal to Qt::AlignHCenter | Qt::AlignVCenter
		label->move(40 + i % 4 * 90, 150 + i / 4 * 90);
		//mouse event pierce through
		//label 挡住button
		label->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	}
}

void ChooseLevelScene::paintEvent(QPaintEvent*)
{
	QPainter painter(this);
	QPixmap pix;
	//background
	pix.load(":/res/OtherSceneBg.png");
	painter.drawPixmap(0, 0, this->width(), this->height(), pix);
	//title
	pix.load(":/res/Title.png");
	painter.drawPixmap((this->width() - pix.width()) * 0.5, 30, pix.width(), pix.height(), pix);

}

ChooseLevelScene::~ChooseLevelScene()
{
}
