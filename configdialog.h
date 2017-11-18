#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QLineEdit>

class ConfigDialog : public QDialog
{
	Q_OBJECT
public:
	explicit ConfigDialog(QWidget *parent = 0);
	QString getSSID();
	QString getPassword();
	quint32 getIP();
	quint32 getMask();
public slots:
	void setSSID(QString);
	void setPassword(QString);
	void setIP(quint32);
	void setMask(quint32);
private:
	QLineEdit *mSSIDField;
	QLineEdit *mPasswordField;
	QLineEdit *mIPField;
	QLineEdit *mMaskField;
	QDialogButtonBox *mButtons;
};

#endif // CONFIGDIALOG_H
