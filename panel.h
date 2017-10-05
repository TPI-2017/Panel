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

signals:
    void disconnect();

private slots:
    void on_applyButton_clicked();

    void on_actionQuit_triggered();

    void on_actionEspaniol_triggered();

    void on_actionEnglish_triggered();

    void on_actionDisconnect_triggered();

    void showWindow();

private:
    Ui::Panel *ui;
};

#endif // PANEL_H
