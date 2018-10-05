#include <QtGui>
#include <QPushButton>
#include <QGridLayout>
#include <QFileDialog>
#include <QMessageBox>
#include "meinWidget.h"

meinWidget::meinWidget(QWidget *parent) : QWidget(parent)
{
    QPushButton *start = new QPushButton(tr("Start"));
    start->setFont(QFont("Times", 18, QFont::Bold));
    connect(start, SIGNAL(clicked()), this, SLOT(startFile()));

    QPushButton *stop = new QPushButton(tr("Stop"));
    stop->setFont(QFont("Times", 16, QFont::Normal));
    connect(stop, SIGNAL(clicked()), this, SLOT(stopFile()));

    QPushButton *save = new QPushButton(tr("Save"));
    save->setFont(QFont("Times", 16, QFont::Normal));
    connect(save, SIGNAL(clicked()), this, SLOT(saveFile()));

    QPushButton *load = new QPushButton(tr("Load"));
    load->setFont(QFont("Times", 16, QFont::Normal));
    connect(load, SIGNAL(clicked()), this, SLOT(loadFile()));

    QPushButton *leave = new QPushButton(tr("Leave"));
    leave->setFont(QFont("Times", 16, QFont::Normal));
    connect(leave, SIGNAL(clicked()), qApp, SLOT(leave()));

    meinZeichenFeld->setFixedSize(700, 700);

    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(start, 0, 0);
    gridLayout->addWidget(stop, 1, 0);
    gridLayout->addWidget(save, 2, 0);
    gridLayout->addWidget(load, 3, 0);
    gridLayout->addWidget(leave, 4, 0);
    gridLayout->addWidget(meinZeichenFeld,1, 2, 2, 1);
    gridLayout->setColumnStretch(1, 10);
    setLayout(gridLayout);
}

void meinWidget::startFile(void){
    meinZeichenFeld->startFile();
}

void meinWidget::stopFile(void){
    meinZeichenFeld->stopFile();
}

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
