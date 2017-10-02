#include "panel.h"
#include "ui_panel.h"
#include <QMessageBox>
#include <string>

using namespace std;

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
    QString text = ui->textMessageField->text();
    QMessageBox::information(this, tr("Aviso"), tr("Se aplica los siguientes items: %1").arg(text));
}

void Panel::on_actionQuit_triggered()
{
    close();
}
