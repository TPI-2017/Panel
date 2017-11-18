#include "configdialog.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLabel>

ConfigDialog::ConfigDialog(QWidget *parent)
: QDialog(parent),
  mSSIDField(new QLineEdit()),
  mPasswordField(new QLineEdit()),
  mIPField(new QLineEdit()),
  mMaskField(new QLineEdit()),
  mButtons(new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel))
{
	QVBoxLayout *layout = new QVBoxLayout();
	QFormLayout *formLayout = new QFormLayout();
	this->setLayout(layout);

	layout->addLayout(formLayout);
	layout->addWidget(mButtons);

	formLayout->addRow(new QLabel(tr("Network Name (SSID):")), mSSIDField);
	formLayout->addRow(new QLabel(tr("Network password:")), mPasswordField);
	formLayout->addRow(new QLabel(tr("IP:")), mIPField);
	formLayout->addRow(new QLabel(tr("Subnet mask:")), mMaskField);

	connect(mButtons, &QDialogButtonBox::accepted, this, &QDialog::accept);
	connect(mButtons, &QDialogButtonBox::rejected, this, &QDialog::reject);

	mPasswordField->setEchoMode(QLineEdit::Password);
}

QString ConfigDialog::getSSID()
{
	return mSSIDField->text();
}

QString ConfigDialog::getPassword()
{
	return mPasswordField->text();
}

QHostAddress ConfigDialog::getIP()
{
	return QHostAddress(mIPField->text());
}

QHostAddress ConfigDialog::getMask()
{
	return QHostAddress(mMaskField->text());
}

void ConfigDialog::setSSID(QString ssid)
{
	mSSIDField->setText(ssid);
}

void ConfigDialog::setPassword(QString password)
{
	mPasswordField->setText(password);
}

void ConfigDialog::setIP(QHostAddress ip)
{
	mIPField->setText(ip.toString());
}


void ConfigDialog::setMask(QHostAddress mask)
{
	mMaskField->setText(mask.toString());
}
