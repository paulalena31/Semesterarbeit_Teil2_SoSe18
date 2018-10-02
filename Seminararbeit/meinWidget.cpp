#include <QtGui>
#include <QPushButton>
#include <QGridLayout>
#include <QFileDialog>
#include <QMessageBox>
#include "meinWidget.h"

meinWidget::meinWidget(QWidget *parent) : QWidget(parent)
{
    QPushButton *quit = new QPushButton(tr("Leave"));
    quit->setFont(QFont("Times", 18, QFont::Bold));
    connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));

    QPushButton *save = new QPushButton(tr("Save"));
    save->setFont(QFont("Times", 18, QFont::Bold));
    connect(save, SIGNAL(clicked()), this, SLOT(saveFile()));

    QPushButton *load = new QPushButton(tr("Load"));
    load->setFont(QFont("Times", 18, QFont::Bold));
    connect(load, SIGNAL(clicked()), this, SLOT(loadFile()));

    QPushButton *start = new QPushButton(tr("Start"));
    start->setFont(QFont("Times", 18, QFont::Bold));
    connect(start, SIGNAL(clicked()), qApp, SLOT(startFile()));

    /*QPushButton *circleButton = new QPushButton(tr("Kreis"));
        circleButton->setFont(QFont("Times", 18, QFont::Bold));
        connect(circleButton, SIGNAL(clicked()), this, SLOT(circle()));*/

    meinZeichenFeld->setFixedSize(700, 700);

    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(quit, 3, 0);
    gridLayout->addWidget(save, 1, 0);
    gridLayout->addWidget(load, 2, 0);
    gridLayout->addWidget(start, 0, 0);
    //gridLayout->addWidget(circleButton, 4, 0);
    gridLayout->addWidget(meinZeichenFeld,1, 2, 2, 1);
    gridLayout->setColumnStretch(1, 10);
    setLayout(gridLayout);

}

/*void meinWidget::circle(void)
{
    meinZeichenFeld->placeObject(zeichenFeld::circle);
} */

void meinWidget::saveFile(){

    QFileDialog dialog(this);
    QString fileName;
    QFile file;

    dialog.setFileMode(QFileDialog::AnyFile);
    fileName = dialog.getSaveFileName(this,
                                      tr("Speichern als"), ".", tr("Zeichnungen (*.myz)"));

    if (fileName.isNull()==false)
    {
        file.setFileName(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QMessageBox::warning(this, tr("Dateifehler"),
                                 tr("Folgende Datei kann nicht verwendet werden: ") + fileName,QMessageBox::Ok);
        }

        meinZeichenFeld->serialize(file);
        file.close();
        return;
    }
}
void meinWidget::loadFile(void)
{
    QFileDialog dialog(this);
    QString fileName;
    QFile file;

    dialog.setFileMode(QFileDialog::AnyFile);
    fileName = dialog.getOpenFileName(this,
                                      tr("Speichern als"), ".", tr("Zeichnungen (*.myz)"));

    if (fileName.isNull()==false)
    {
        file.setFileName(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::warning(this, tr("Dateifehler"),
                                 tr("Folgende Datei kann nicht geÃ¶ffnet werden: ") + fileName,QMessageBox::Ok);
        }

        meinZeichenFeld->deserialize(file);
        file.close();
        return;
    }
}
