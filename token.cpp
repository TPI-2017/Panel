#include "token.h"
#include "ui_token.h"
#include <QDebug>

const char* Token::TOKEN_EXP;
QSettings* Token::setting;
QString Token::SETTING_KEY;

Token::Token(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Token)
{
    ui->setupUi(this);
    QRegExp regExp(Token::getTokenExp());
    ui->tokenInput->setValidator(new QRegExpValidator(regExp, this));
    ui->tokenRepeatInput->setValidator(new QRegExpValidator(regExp, this));
}

Token::~Token()
{
    delete ui;
}

void Token::initStaticVars(){
    TOKEN_EXP = "^\\S+";
    setting = new QSettings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    SETTING_KEY = "token";
}

std::string Token::getToken(){
    return setting->value(SETTING_KEY).toString().toStdString();
}

char* Token::getTokenExp(){
    return (char*)TOKEN_EXP;
}


void Token::on_cancelButton_clicked()
{
    this->hide();
    ui->tokenRepeatInput->setText("");
    ui->tokenRepeatInput->setStyleSheet("color: black");
    ui->tokenInput->setText("");
    ui->tokenInput->setStyleSheet("color: black");
}

void Token::on_applyButton_clicked()
{
    std::string newToken = ui->tokenInput->text().toStdString();
    std::string newRepeatToken = ui->tokenRepeatInput->text().toStdString();

    if (!newToken.compare(newRepeatToken)) {
        this->on_cancelButton_clicked();
        setting->setValue(SETTING_KEY, newToken.c_str());
        std::string str = "- set: " + setting->value(SETTING_KEY).toString().toStdString();
        qDebug() << str.c_str();
    } else {
        ui->tokenInput->setStyleSheet("color: red");
        ui->tokenRepeatInput->setStyleSheet("color: red");
    }
}
