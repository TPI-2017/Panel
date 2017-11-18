#ifndef LOGIN_DIALOG_H
#define LOGIN_DIALOG_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QSettings>

class LoginDialog : public QDialog
{
    Q_OBJECT
public:
	explicit LoginDialog(QWidget *parent = 0);
	QString getPassword();
	QString getHostname();
private:
	QLineEdit *mHostnameField;
	QLineEdit *mPasswordField;
	QDialogButtonBox *mButtons;
	QSettings *mSettings;
};

#endif
