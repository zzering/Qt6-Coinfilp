#include "chooselevelscene.h"
#include<qmenubar.h>
#include<QSoundEffect>
#include<QPainter>
#include<QPixmap>
#include"jumppushbutton.h"
#include<QTimer>
#include<QLabel>
#include"playscene.h"

ChooseLevelScene::ChooseLevelScene(QWidget *parent)
    : QMainWindow{parent}
{
    this->setFixedSize(400, 700);
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    this->setWindowTitle("选择关卡");
    QMenuBar* bar = this->menuBar();
    this->setMenuBar(bar);
    QMenu* startMenu = bar->addMenu("开始");
    QAction* quitAction = startMenu->addAction("退出");

    connect(quitAction, &QAction::triggered, [=]() {
        this->close(); });
    QSoundEffect* chooseSound = new QSoundEffect;
    chooseSound->setSource(QUrl::fromLocalFile(":/res/TapButtonSound.wav"));

    //        chooseSound->play();
    QSoundEffect* backSound = new QSoundEffect;
    backSound->setSource(QUrl::fromLocalFile(":/res/BackButtonSound.wav"));

    //backBtn
    JumpPushButton* backBtn = new JumpPushButton(":/res/BackButton.png", ":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width(), this->height() - backBtn->height());
    connect(backBtn, &JumpPushButton::clicked, [=]() {
        backSound->play();
        QTimer::singleShot(50, this, [=]() {
            //触发自定义信号，关闭自身，该信号写到 signals下做声明
            emit this->chooseSceneBack();
        });
    });
    //creat choose level btn
    for (int i = 0; i < 20; i++) {
        JumpPushButton* menuBtn = new JumpPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(40 + i % 4 * 90, 150 + i / 4 * 90);
        //monitor every level btn event
        connect(menuBtn, &JumpPushButton::clicked, [=]() {
            chooseSound->play();
            //QString str = QString("选择的是第%1关").arg(i + 1);
            //qDebug() << str;
            this->hide();	//hide level scence
            pScene = new PlayScene(i + 1);//creat game scence

            pScene->setGeometry(this->geometry());
            pScene->show();
            //monitor back btn in playscene
            connect(pScene, &PlayScene::chooseSceneBack, [=]() {
                this->setGeometry(pScene->geometry());
                backSound->play();
                this->show();
                delete pScene;
                pScene = Q_NULLPTR;
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
        //label bolck button
        label->setAttribute(Qt::WA_TransparentForMouseEvents, true);

    }
}

void ChooseLevelScene::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix.width(),pix.height(),pix);

}











