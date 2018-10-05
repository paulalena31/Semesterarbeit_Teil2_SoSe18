#include <QtGui>
#include <QMessageBox>
#include "zeichenFeld.h"
#include <QTimer>

QPainter painter;
 
zeichenFeld::zeichenFeld(QWidget *parent) : QWidget(parent)
{
    setPalette(QPalette(QColor(175, 238, 238)));
    setAutoFillBackground(true);
    setFocusPolicy(Qt::StrongFocus);

    timer = new QTimer(this);
    connect (timer, SIGNAL(timeout()),this, SLOT(update()));

    startY1 = -100;
    startY2 = -100;
    startY3 = -100;

    increment1 = 0;
    increment2 = 0;
    increment3 = 0;
}

void zeichenFeld::paintEvent(QPaintEvent *event)
{
    QPainter painter, painter1, painter2, painter3;
    int Y1, Y2, Y3;

    Y1 = startY1;
    Y2 = startY2;
    Y3 = startY3;

    painter.begin(this);

    QColor PlayerRectangle ("#0000FF");
    Qt::BrushStyle StylePlayerRectangle = Qt::BDiagPattern;
    QBrush brushPlayerRectangle (PlayerRectangle, StylePlayerRectangle);
    painter.setBrush(brushPlayerRectangle);

    painter.setPen(QPen(Qt::blue, 2));
    painter.drawRect(x, y, 60, 60);
    painter.setPen(QPen(Qt::red,2));
    painter.setBrush(Qt::red);
    painter.drawEllipse(a, b, 30, 30);
    painter.drawEllipse(a - 40, b, 30, 30);
    painter.drawEllipse(a - 80, b, 30, 30);

    QFont font = painter.font();
    font.setPixelSize(35);
    painter.setFont(font);
    painter.setPen(QPen(Qt:: black, 2));
    painter.drawText(c, d, "Punkte: ");


    //Objekt1
    painter1.begin(this);
    QColor Rect1((Qt::blue));
    Qt::BrushStyle styleRect1 = Qt::SolidPattern;
    QBrush brushRect1(Rect1, styleRect1);
    painter1.setBrush(brushRect1);
    painter1.drawRect(400,Y1,60,60);

    if (increment1) {
            if (startY1 <=700) startY1=startY1+4;
            else startY1=-100;
        }

    //Objekt2
    painter2.begin(this);
    QColor Rect2((Qt::lightGray));
    Qt::BrushStyle styleRect2 = Qt::SolidPattern;
    QBrush brushRect2(Rect2, styleRect2);
    painter2.setBrush(brushRect2);
    painter2.drawRect(500,Y2,70,70);

    if (increment2) {
            if (startY2 <=700) startY2=startY2+7;
            else startY2=-100;
        }

    //Objekt3
    painter3.begin(this);
    QColor Ellipse1((Qt::green));
    Qt::BrushStyle styleEllipse1 = Qt::SolidPattern;
    QBrush brushEllipse1(Ellipse1, styleEllipse1);
    painter3.setBrush(brushEllipse1);
    painter3.drawEllipse(200,Y3,50,50);

    if (increment3) {
            if (startY3 <=800) startY3=startY3+6;
            else startY3=-100;
        }

    painter.end();
    painter1.end();
    painter2.end();
    painter3.end();
}

void zeichenFeld::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left)
    {
        if(x>=25)
          x = x - 25;
        update();
    }

    if (event->key() == Qt::Key_Right)
    {
        if(x<650)
          x = x + 25;
        update();
    }
}
void zeichenFeld::serialize(QFile &file)
{
    QTextStream out (&file);

    out << startY1 << endl;
    out << startY2 << endl;
    out << startY3 << endl;


}
void zeichenFeld::deserialize(QFile &file)
{
    QTextStream in(&file);
    //Hilfsvariablen zum Laden der Werte


    int Y1;
    int Y2;
    int Y3;

    in >> Y1 >> endl;
    in >> Y2 >> endl;
    in >> Y3 >> endl;

    startY1 = Y1;
    startY2 = Y2;
    startY3 = Y3;
    update();
}
