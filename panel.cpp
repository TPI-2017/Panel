#include "panel.h"
#include "ui_panel.h"
#include "translation.h"
#include <QMessageBox>
#include <QLocale>

using namespace std;

Panel::Panel(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Panel)
{
    ui->setupUi(this);
    // Traduce la interfaz según el idioma del sistema operativo que usa el cliente
    Translation::translateTo();
}

Panel::~Panel()
{
    delete ui;
}

void Panel::on_applyButton_clicked()
{
    QString text = ui->textMessageField->text();
    QString locale = QLocale::system().name();
    QMessageBox::information(this, tr("Info"), tr("Appling this change: %1\n Idioma:%2").arg(text, locale));
}

void Panel::on_actionQuit_triggered()
{
    close();
}

void Panel::on_actionEspaniol_triggered()
{
    Translation::translateTo(TRANSLATION_ES);
    ui->retranslateUi(this);
}

void Panel::on_actionEnglish_triggered()
{
    Translation::translateTo(TRANSLATION_EN);
    ui->retranslateUi(this);
}
