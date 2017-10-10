#ifndef TOKEN_H
#define TOKEN_H

#include <QWidget>
#include <QSettings>
#include <QString>
#include <string>

namespace Ui {
class Token;
}

class Token : public QWidget
{
    Q_OBJECT

public:
    explicit Token(QWidget *parent = 0);
    ~Token();
    static void initStaticVars();
    static std::string getToken();
    static char* getTokenExp();

private slots:
    void on_cancelButton_clicked();

    void on_applyButton_clicked();

private:
    Ui::Token *ui;
    static const char* TOKEN_EXP;
    static QSettings* setting;
    static QString SETTING_KEY;
};

#endif // TOKEN_H
