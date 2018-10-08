#include <QWidget>
#include "zeichenFeld.h"
#include <QtGui>
#include <QPushButton>
#include <QGridLayout>
#include <QFileDialog>
#include <QMessageBox>

class meinWidget : public QWidget
{
    Q_OBJECT
private:
    zeichenFeld *meinZeichenFeld = new zeichenFeld;

public:
    meinWidget(QWidget *parent = 0);

private slots:
    void loadFile();
    void saveFile();
    void startFile(void);
    void stopFile(void);
};
