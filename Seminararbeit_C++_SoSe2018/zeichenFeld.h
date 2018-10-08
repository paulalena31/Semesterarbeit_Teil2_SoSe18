#include <QWidget>
#include <QFile>
#include <QTimer>
#include <QtGui>
#include <QMessageBox>
#include <iostream>

class zeichenFeld : public QWidget
{
    Q_OBJECT

public:
    zeichenFeld(QWidget *parent = 0);
    void serialize(QFile &file);
    void deserialize(QFile &file);

    void startFile(void) {
		timer->start(25); increment1 = true, increment2 = true, increment3 = true;
		Playtime.start();
    }

    void stopFile(void) {
		timer->stop(); increment1 = false, increment2 = false, increment3 = false;
	}

private:

	void updateObjects();
	bool HitRegistration();

	QTimer *timer;

    QElapsedTimer Playtime; //fängt immer wieder von Null an
    int objectCounter = 0; //zählt nach Stop vom vorherigen Wert aus weiter

    int x=350, y=620;
    int a=650, b=30;
    int c=20, d=50;

	int life = 3;
    bool Object1Col = false, Object2Col = false, Object3Col = false;


    int startY1, startY2, startY3;

    bool increment1, increment2, increment3;

protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
};
