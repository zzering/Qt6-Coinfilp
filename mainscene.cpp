#include "mainscene.h"
#include "ui_mainscene.h"
#include<QPainter>
#include"jumppushbutton.h"
#include<QTimer>
#include<QSoundEffect>


MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);
    //mainscence configuration in constructor function
    this->setFixedSize(400, 700);
    this->setWindowIcon(QPixmap(":/res/go.ico"));
    this->setWindowTitle("CoinFlip");
    //menubar quit
    connect(ui->actionQuit, &QAction::triggered, [=]() {
        this->close();
    });
    JumpPushButton *startBtn=new JumpPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.8);

    chooseScene=new ChooseLevelScene;
    //monitor the backbutton of choose level scence
    connect(chooseScene, &ChooseLevelScene::chooseSceneBack, this, [=]() {
        //设置this场景位置
        this->setGeometry(chooseScene->geometry());
        chooseScene->hide();//hide the scence of chooselevel
        this->show();//reshow the mainscence
        });

    connect(startBtn, &JumpPushButton::clicked, [=]() {
        QSoundEffect *startSound=new QSoundEffect;
        startSound->setSource(QUrl::fromLocalFile(":/res/TapButtonSound.wav"));
        startSound->play();
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
    //stretch to current width and height
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);
    //title of coinflip
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width() * 0.6, pix.height() * 0.6);
    painter.drawPixmap(10, 30, pix);//, width(), pix, height(), pix);
}

MainScene::~MainScene()
{
    delete ui;
}

