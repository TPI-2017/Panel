#include "panel.h"
#include "ui_panel.h"
#include "translation.h"
#include <QMessageBox>

Panel::Panel(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Panel)
{
    ui->setupUi(this);
}

Panel::~Panel()
{
    delete ui;
}

void Panel::on_applyButton_clicked()
{
}

void Panel::on_actionQuit_triggered()
{
    close();
}

void Panel::on_actionEspaniol_triggered()
{
    Translation::translate(Translation::Spanish);
    ui->retranslateUi(this);
}

void Panel::on_actionEnglish_triggered()
{
    Translation::translate(Translation::English);
    ui->retranslateUi(this);
}

void Panel::on_actionDisconnect_triggered()
{
    close();
    disconnect();
}

void Panel::showWindow()
{
    this->show();
}


