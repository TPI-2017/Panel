#include "login_dialog.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLabel>

LoginDialog::LoginDialog(QWidget *parent)
: QDialog(parent),
  mHostnameField(new QLineEdit()),
  mPasswordField(new QLineEdit()),
  mButtons(new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel))
{
	QVBoxLayout *layout = new QVBoxLayout();
	QFormLayout *formLayout = new QFormLayout();
	this->setLayout(layout);
	
	layout->addLayout(formLayout);
	layout->addWidget(mButtons);
	
	formLayout->addRow(new QLabel(tr("Host:")), mHostnameField);
	formLayout->addRow(new QLabel(tr("Password:")), mPasswordField);
	
	connect(mButtons, &QDialogButtonBox::accepted, this, QDialog::accept);
	connect(mButtons, &QDialogButtonBox::rejected, this, QDialog::rejected);
	
	mPasswordField->setEchoMode(QLineEdit::Password);

	show();
}

QString LoginDialog::getPassword()
{
	return mPasswordField->text();
}

QString LoginDialog::getHostname()
{
	return mHostnameField->text();
}