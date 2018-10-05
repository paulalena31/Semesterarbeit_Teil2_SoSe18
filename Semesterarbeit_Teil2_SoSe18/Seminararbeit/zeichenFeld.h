#include <QWidget>
#include <QFile>
#include <QTimer>
 
class zeichenFeld : public QWidget
{
    Q_OBJECT

    public:
    zeichenFeld(QWidget *parent = 0);
    void serialize(QFile &file);
    void deserialize(QFile &file);

    void startFile(void) {
        timer->start(25); increment1 = 1, increment2 = 1, increment3 =1;
    };

    void stopFile(void) {
        timer->stop(); increment1 = 0, increment2 = 0, increment3 =0;
    };

    private:

    QTimer *timer;

    int x=350, y=620;
    int a=650, b=30;
    int c=20, d=50;

    int Y1, Y2, Y3;

    int startY1, startY2, startY3;

    int increment1;
    int increment2;
    int increment3;

    protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
};
