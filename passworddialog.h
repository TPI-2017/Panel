#ifndef PASSWORDCHANGEDIALOG_H
#define PASSWORDCHANGEDIALOG_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QLineEdit>

class PasswordDialog : public QDialog
{
	Q_OBJECT
public:
	explicit PasswordDialog(QWidget *parent = 0);
	QString getPassword();
private:
	QLineEdit *mPasswordField;
	QDialogButtonBox *mButtons;

};
#endif // PASSWORDCHANGEDIALOG_H
