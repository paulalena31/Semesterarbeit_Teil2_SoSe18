#include <QtGui>
#include <QMessageBox>
#include "zeichenFeld.h"

QPainter painter;
 
zeichenFeld::zeichenFeld(QWidget *parent) : QWidget(parent)
{
    setPalette(QPalette(QColor(175, 238, 238)));
    setAutoFillBackground(true);
}

void zeichenFeld::paintEvent(QPaintEvent *event)
{
    painter.begin(this);
    painter.setPen(QPen(Qt::blue, 2));
    painter.drawRect(x, y, 30, 30);
    painter.setPen(QPen(Qt::red,2));
    painter.drawEllipse(a, b, 30, 30);
    painter.end();
}

void zeichenFeld::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::LeftArrow)
    {
        if(x>=25)
          x = x - 25;
        update();
    }

    if (event->key() == Qt::RightArrow)
    {
        if(x<450)
          x = x + 25;
        update();
    }
}
void zeichenFeld::serialize(QFile &file)
{
   // vector<struct myPoint *>::iterator pos;

    QTextStream out(&file);

    //for (pos=points.begin();pos!=points.end();pos++)
    //{
        out  << "p "<< x;
     //        << (*pos)->color.red() << " " << (*pos)->color.green() << " "
       //      << (*pos)->color.blue() << " " << (*pos)->width << " "
         //    << (*pos)->point.x() << " " << (*pos)->point.y() << endl;
   // }
}
void zeichenFeld::deserialize(QFile &file)
{
    //struct myPoint *point;
    char c;
    //int red, green, blue, x, y;

    QTextStream in(&file);

    while (in.status() == QTextStream::Ok)
    {
        in >> c;
       if (in.status() == QTextStream::ReadPastEnd) break;

        if (c!='p')
        {
            QMessageBox::warning(this, tr("Objektfehler"),
                                 tr("Folgender Objekttyp ist unbekannt: ") + c,QMessageBox::Ok);
            return;
        }

        in >> x; // Leerstellen werden vom '>>' Operator 'konmsumiert';
        // Zeilenenden nicht.


    }

    update();
}
