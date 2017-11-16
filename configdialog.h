#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QHostAddress>

class ConfigDialog : public QDialog
{
	Q_OBJECT
public:
	explicit ConfigDialog(QWidget *parent = 0);
	QString getSSID();
	QString getPassword();
	QHostAddress getIP();
	QHostAddress getMask();
private:
	QLineEdit *mSSIDField;
	QLineEdit *mPasswordField;
	QLineEdit *mIPField;
	QLineEdit *mMaskField;
	QDialogButtonBox *mButtons;
};

#endif // CONFIGDIALOG_H
