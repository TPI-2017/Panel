#include "login.h"
#include "ui_login.h"
#include <QtDebug>
#include <QRegExpValidator>

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    QRegExp regExp(TOKEN_EXP);
    ui->tokenInput->setValidator(new QRegExpValidator(regExp, this));
}

Login::~Login()
{
    delete ui;
}

void Login::on_loginButton_clicked()
{
    std::string token = ui->tokenInput->text().toStdString();
    if (TOKEN_VALID == token) {
        this->hide();
        ui->tokenInput->setText("");
        ui->tokenInput->setStyleSheet("color: black");
        accessPermited();
    } else {
        ui->tokenInput->setStyleSheet("color: red");
    }
}

void Login::showWindow()
{
    ui->retranslateUi(this);
    this->show();
}
