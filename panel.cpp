#include "panel.h"
#include "ui_panel.h"
#include <QMessageBox>
#include <QTranslator>

using namespace std;

QTranslator translator, defaultTranslator;

Panel::Panel(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Panel)
{
    ui->setupUi(this);
    QApplication::instance()->installTranslator(&translator);
}

Panel::~Panel()
{
    delete ui;
}

void Panel::on_applyButton_clicked()
{
    QString text = ui->textMessageField->text();
    QMessageBox::information(this, tr("Info"), tr("Appling this change: %1").arg(text));
}

void Panel::on_actionQuit_triggered()
{
    close();
}

void Panel::on_actionEspaniol_triggered()
{
    translator.load(":/es.qm");
    QApplication::instance()->installTranslator(&translator);
    ui->retranslateUi(this);
}

void Panel::on_actionEnglish_triggered()
{
    translator.load(":/en.qm");
    QApplication::instance()->installTranslator(&translator);
    ui->retranslateUi(this);
}
