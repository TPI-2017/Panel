#include "passworddialog.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLabel>

PasswordDialog::PasswordDialog(QWidget *parent)
: QDialog(parent),
  mPasswordField(new QLineEdit()),
  mButtons(new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel))
{
	QVBoxLayout *layout = new QVBoxLayout();
	QFormLayout *formLayout = new QFormLayout();
	this->setLayout(layout);

	layout->addLayout(formLayout);
	layout->addWidget(mButtons);

	formLayout->addRow(new QLabel(tr("Password:")), mPasswordField);

	connect(mButtons, &QDialogButtonBox::accepted, this, &QDialog::accept);
	connect(mButtons, &QDialogButtonBox::rejected, this, &QDialog::reject);
	mPasswordField->setEchoMode(QLineEdit::Password);
	mPasswordField->setFocus(Qt::NoFocusReason);
}

QString PasswordDialog::getPassword()
{
	return mPasswordField->text();
}
