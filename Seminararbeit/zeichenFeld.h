#include <QWidget>
#include <QFile>
 
class zeichenFeld : public QWidget
{
    Q_OBJECT

    public:
    zeichenFeld(QWidget *parent = 0);
    void serialize(QFile &file);
    void deserialize(QFile &file);

    private:
    int x=350, y=650;
    int a=650, b=30;

    protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
};
