#include "logindialog.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLabel>

LoginDialog::LoginDialog(QWidget *parent)
: QDialog(parent),
  mHostnameField(new QLineEdit()),
  mPasswordField(new QLineEdit()),
  mButtons(new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel)),
  mSettings(new QSettings("ANRS - TPI2017"))
{
	QVBoxLayout *layout = new QVBoxLayout();
	QFormLayout *formLayout = new QFormLayout();
	this->setLayout(layout);

	layout->addLayout(formLayout);
	layout->addWidget(mButtons);

	formLayout->addRow(new QLabel(tr("Host:")), mHostnameField);
	formLayout->addRow(new QLabel(tr("Password:")), mPasswordField);

	connect(mButtons, &QDialogButtonBox::accepted, this, &QDialog::accept);
	connect(mButtons, &QDialogButtonBox::rejected, this, &QDialog::reject);
	mPasswordField->setEchoMode(QLineEdit::Password);
	QString hostname = mSettings->value("Hostname").toString();
	mHostnameField->setText(hostname);

	if (hostname.length() == 0)
		mHostnameField->setFocus(Qt::NoFocusReason);
	else
		mPasswordField->setFocus(Qt::NoFocusReason);
}

QString LoginDialog::getPassword()
{
	return mPasswordField->text();
}

QString LoginDialog::getHostname()
{
	QString hostname = mHostnameField->text();
	mSettings->setValue("Hostname", hostname);
	return hostname;
}
