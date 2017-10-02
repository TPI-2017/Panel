#ifndef PANEL_H
#define PANEL_H

#include <QMainWindow>
#include <QApplication>

namespace Ui {
class Panel;
}

class Panel : public QMainWindow
{
    Q_OBJECT

public:
    explicit Panel(QWidget *parent = 0);
    ~Panel();

private slots:
    void on_applyButton_clicked();

    void on_actionQuit_triggered();

    void on_actionEspaniol_triggered();

    void on_actionEnglish_triggered();

private:
    Ui::Panel *ui;
};

#endif // PANEL_H
