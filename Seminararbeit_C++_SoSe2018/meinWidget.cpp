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

    QPushButton *quit = new QPushButton(tr("Leave"));
    quit->setFont(QFont("Times", 16, QFont::Normal));
    connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));

    meinZeichenFeld->setFixedSize(700, 700);

    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(start, 0, 0);
    gridLayout->addWidget(stop, 1, 0);
    gridLayout->addWidget(save, 2, 0);
    gridLayout->addWidget(load, 3, 0);
    gridLayout->addWidget(quit, 4, 0);
	gridLayout->addWidget(meinZeichenFeld,0, 1, 5, 1);
    gridLayout->setColumnStretch(1, 10);
    setLayout(gridLayout);
}

void meinWidget::startFile(void){
    meinZeichenFeld->startFile();
}

void meinWidget::stopFile(void){
    meinZeichenFeld->stopFile();
}

//Speichern
void meinWidget::saveFile(){

    QFileDialog dialog(this);
    QString fileName;
    QFile file;

	meinZeichenFeld->stopFile();
    dialog.setFileMode(QFileDialog::AnyFile);
	fileName = dialog.getSaveFileName(this, "Speichern als", ".", "Zeichnungen (*.myz)");

	if (fileName.isNull())
		return;

	file.setFileName(fileName);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		QMessageBox::warning(this, "Dateifehler","Folgende Datei kann nicht verwendet werden: " + fileName,QMessageBox::Ok);
		return;
	}

	meinZeichenFeld->serialize(file);
	file.close();
}

//Laden
void meinWidget::loadFile(void)
{
    QFileDialog dialog(this);
    QString fileName;
    QFile file;

    dialog.setFileMode(QFileDialog::AnyFile);
	fileName = dialog.getOpenFileName(this, "Laden", ".", "Zeichnungen (*.myz)");

	if (fileName.isNull())
		return;

	file.setFileName(fileName);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QMessageBox::warning(this, "Dateifehler", "Folgende Datei kann nicht geÃ¶ffnet werden: " + fileName,QMessageBox::Ok);
		return;
	}

	meinZeichenFeld->deserialize(file);
	file.close();
}
