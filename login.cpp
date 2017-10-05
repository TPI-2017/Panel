#include "login.h"
#include "ui_login.h"
#include <QtDebug>

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::on_loginButton_clicked()
{
    std::string token = ui->tokenInput->text().toStdString();
    qDebug() << ui->tokenInput->text();
    if (TOKEN_VALID == token) {
        this->hide();
        ui->tokenInput->setText("");
        accessPermited();
    }
}

void Login::showWindow()
{
    this->show();
}
