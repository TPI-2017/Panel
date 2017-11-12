#include "panel.h"
#include "ui_panel.h"
#include "translation.h"
#include "login_dialog.h"
#include <QMessageBox>

Panel::Panel(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Panel),
    mClient(new Client())
{
    ui->setupUi(this);
    show();
    LoginDialog *loginDialog = new LoginDialog(this);
    int result = loginDialog->exec();
    
    if (result != QDialog::Accepted)
    	this->close();
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

void Panel::on_actionAbout_triggered()
{
    QMessageBox::information(this, tr("Authors"),
                            tr("\nLED Display - © 2017\n\n"
                            "García, Agustín\nLevy, Santiago\n"
                            "Romero Dapozo, Ramiro\nTernouski, Sebastian Nahuel\n"),
                            QMessageBox::Ok, 0);
}

void Panel::on_actionChange_token_triggered()
{
}
