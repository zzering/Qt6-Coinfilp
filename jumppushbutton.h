#ifndef JUMPPUSHBUTTON_H
#define JUMPPUSHBUTTON_H

#include<QPushButton>

class JumpPushButton : public QPushButton
{
//    Q_OBJECT
public:
    JumpPushButton(QString normalImg,QString pressImg="");
    void jumpDown();
    void jumpUp();
    void mousePressEvent(QMouseEvent*e);
    void mouseReleaseEvent(QMouseEvent*e);
    //normalImgPath saves the path of the normally displayed picture
    QString normalImgPath;
    //pressImgPath saves the path of the picture after pressed
    QString pressImgPath;

};

#endif // JUMPPUSHBUTTON_H
