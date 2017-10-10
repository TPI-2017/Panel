#include "panel.h"
#include "ui_panel.h"
#include "translation.h"
#include <QMessageBox>

Panel::Panel(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Panel)
{
    ui->setupUi(this);
    token_change = new Token();
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

void Panel::on_actionAbout_triggered()
{
    QMessageBox::information(this, tr("Authors"),
                            tr("\nLED Display - © 2017\n\n"
                            "Garcı́a, Agustı́n\nLevy, Santiago\n"
                            "Romero Dapozo, Ramiro\nTernouski, Sebastian Nahuel\n"),
                            QMessageBox::Ok, 0);
}

void Panel::on_actionChange_token_triggered()
{
    token_change->show();
}
