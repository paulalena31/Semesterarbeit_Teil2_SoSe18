#include "zeichenFeld.h"

QPainter painter;
 
zeichenFeld::zeichenFeld(QWidget *parent) : QWidget(parent)
{
    setPalette(QPalette(QColor(064, 224, 208)));
    setAutoFillBackground(true);
    setFocusPolicy(Qt::StrongFocus);

    timer = new QTimer(this);
    connect (timer, SIGNAL(timeout()),this, SLOT(update()));

    startY1 = -100;
    startY2 = -100;
    startY3 = -100;

    increment1 = false;
	increment2 = false;
	increment3 = false;

	objectCounter = 0;
	life = 3;
	Object1Col, Object2Col, Object3Col = false;
}

void zeichenFeld::paintEvent(QPaintEvent *event)
{
    QPainter painter, painter1, painter2, painter3;

    painter.begin(this);

    //Avatar
    QColor PlayerRectangle ("#0000FF");
    Qt::BrushStyle StylePlayerRectangle = Qt::BDiagPattern;
    QBrush brushPlayerRectangle (PlayerRectangle, StylePlayerRectangle);
    painter.setBrush(brushPlayerRectangle);
    painter.setPen(QPen(Qt::blue, 2));
    painter.drawRect(x, y, 60, 60);

    //Kreise für Leben
    painter.setPen(QPen(Qt::red,2));
	painter.setBrush(Qt::transparent);
	if(life >= 3)
		painter.setBrush(Qt::red);
    painter.drawEllipse(a, b, 30, 30);
	if(life >= 2)
		painter.setBrush(Qt::red);
    painter.drawEllipse(a - 40, b, 30, 30);
	if(life >= 1)
		painter.setBrush(Qt::red);
    painter.drawEllipse(a - 80, b, 30, 30);
	if(life <= 0)
		stopFile();

    QFont font = painter.font();
    font.setPixelSize(35);
    painter.setFont(font);
    painter.setPen(QPen(Qt:: black, 2));

    //Punkte Zähler
    std::string temp("Punkte: " + std::to_string(objectCounter)); //hängt die Nummer an den String dran
	if(Playtime.isValid())
        temp.append(" (" + std::to_string(Playtime.elapsed()/(float)1000) + " s)"); //hängt die Spielzeit an den String dran, wenn Start geklickt wird
    painter.drawText(c, d, temp.c_str()); //wandelt den c++ std::string in einen c string um


    //Objekt1 blaues Rechteck
    painter1.begin(this);
    QColor Rect1((Qt::blue));
    Qt::BrushStyle styleRect1 = Qt::SolidPattern;
    QBrush brushRect1(Rect1, styleRect1);
    painter1.setBrush(brushRect1);
	painter1.drawRect(400,startY1,60,60);

    //Objekt2 graues Rechteck
    painter2.begin(this);
    QColor Rect2((Qt::lightGray));
    Qt::BrushStyle styleRect2 = Qt::SolidPattern;
    QBrush brushRect2(Rect2, styleRect2);
    painter2.setBrush(brushRect2);
	painter2.drawRect(500,startY2,70,70);

    //Objekt3 gelber Kreis
    painter3.begin(this);
    QColor Ellipse1((Qt::yellow));
    Qt::BrushStyle styleEllipse1 = Qt::SolidPattern;
    QBrush brushEllipse1(Ellipse1, styleEllipse1);
    painter3.setBrush(brushEllipse1);
	painter3.drawEllipse(200,startY3,50,50);

	updateObjects();
	if(HitRegistration())
		life--;

    painter.end();
    painter1.end();
    painter2.end();
    painter3.end();

}

//herunterfallende Objekte
void zeichenFeld::updateObjects(){
	if (increment1) {
		if (startY1 <= 700)
            startY1 += 4;
		else {
			startY1 = -100;
			Object1Col = false;
			objectCounter ++;
		}
	}

	if (increment2) {
		if (startY2 <= 700)
            startY2 += 7;
		else {
			startY2 = -100;
			Object2Col = false;
			objectCounter ++;
		}
	}

	if (increment3) {
		if (startY3 <= 800)
            startY3 += 6;
		else {
			startY3 = -100;
			Object3Col = false;
			objectCounter ++;
		}
	}
}

//Funktion für den Kollision des Avatars mit den Objekten
bool zeichenFeld::HitRegistration(){
	if(startY1 + 60 > y && !Object1Col){
		if(x + 60 > 400 && x < 400 + 60){
			Object1Col = true;
			return true;
		}
	}
	if(startY2 + 70 > y && !Object2Col){
		if(x + 60 > 500 && x < 500 + 70){
			Object2Col = true;
			return true;
		}
	}
	if(startY1 + 50 > y && !Object3Col){
		if(x + 60 > 200 && x < 200 + 50){
			Object3Col = true;
			return true;
		}
	}
	return false;
}

//Funktion für die Bewegung des Avatars
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
    out << x << endl; //speichert den Avatar
    out << objectCounter << endl;
	out << life << endl;

}
void zeichenFeld::deserialize(QFile &file)
{
    QTextStream in(&file);

	in >> startY1 >> endl;
	in >> startY2 >> endl;
	in >> startY3 >> endl;
    in >> x >> endl; //läd den Avatar
    in >> objectCounter >> endl;
    in >> life >> endl;

    update();
}
