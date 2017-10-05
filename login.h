#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

signals:
    void accessPermited();

private slots:
    void on_loginButton_clicked();
    void showWindow();

private:
    Ui::Login *ui;
    const std::string TOKEN_VALID = "lacartel";
    const char* TOKEN_EXP         = "^\\S+";
};

#endif // LOGIN_H