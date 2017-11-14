#include "panel.h"
#include "ui_panel.h"
#include "translation.h"
#include "login_dialog.h"
#include <QMessageBox>

Panel::Panel(QWidget *parent)
: QMainWindow(parent),
  ui(new Ui::Panel),
  mClient(new Client()),
  mClientThread(new QThread())
{
	ui->setupUi(this);
}

void Panel::init()
{
	show();
	
	mClient->moveToThread(mClientThread);
	QObject::connect(this, &Panel::applyRequested, mClient, &Client::apply);
	QObject::connect(this, &Panel::restoreRequested, mClient, &Client::restore);
	QObject::connect(this, &Panel::hostnameChanged, mClient, &Client::setHostname);
	QObject::connect(this, &Panel::passwordChanged, mClient, &Client::setWorkingPassword);
	QObject::connect(mClient, &Client::done, this, &Panel::clientDone);

	mClientThread->start();
	
	LoginDialog *loginDialog = new LoginDialog(this);
	int result = loginDialog->exec();
	
	if (result != QDialog::Accepted) {
		close();
		return;
	}
	emit hostnameChanged(loginDialog->getHostname());
	emit passwordChanged(loginDialog->getPassword());
	
	restoreSettings();
}

Panel::~Panel()
{
	delete ui;
}

void Panel::on_applyButton_clicked()
{
	this->setEnabled(false);
}

void Panel::on_actionQuit_triggered()
{
	close();
}

void Panel::on_actionEspaniol_triggered()
{
	Translation::translate(Translation::Spanish);
	ui->retranslateUi(this);
}

void Panel::on_actionEnglish_triggered()
{
	Translation::translate(Translation::English);
	ui->retranslateUi(this);
}

void Panel::on_actionDisconnect_triggered()
{
	close();
}

void Panel::on_actionAbout_triggered()
{
	QMessageBox::information(this, tr("Authors"),
			    tr("\nLED Display - © 2017\n\n"
			    "García, Agustín\nLevy, Santiago\n"
			    "Romero Dapozo, Ramiro\nTernouski, Sebastian Nahuel\n"),
			    QMessageBox::Ok, 0);
}

void Panel::on_actionChange_token_triggered()
{

}

void Panel::textChanged(QString text)
{
	ui->textMessageField->setPlainText(text);
}

void Panel::restoreSettings()
{
	this->setEnabled(false);
	this->statusBar()->showMessage(tr("Busy"));
	emit restoreRequested();
}

void Panel::applySettings()
{
	this->setEnabled(false);
	this->statusBar()->showMessage(tr("Busy"));
	emit applyRequested();
}

void Panel::clientDone(Client::ClientError status)
{
	this->setEnabled(true);
	this->statusBar()->showMessage(tr("Ready"));
	// TODO: manejar cuando status != Ok
}

void Panel::errorOccurred(Client::ClientError error)
{
	QString errorMessage;
	switch (error) {
	case Client::BadPassword:
		errorMessage = tr("Wrong password.");
		break;
	case Client::BadWifiConfig:
		errorMessage = tr("Wrong Wifi settings.");
		break;
	case Client::BadTextEncoding:
		errorMessage = tr("Text encoding is not Latin-1.");
		break;
	case Client::CertificateMissing:
		errorMessage = tr("Failed to load TLS certificate.");
		break;
	case Client::ResponseTimeout:
		errorMessage = tr("Connection timed out.");
		break;
	case Client::WrongResponse:
		errorMessage = tr("Received invalid response.");
		break;
	case Client::Unknown:
		errorMessage = tr("Unknown error.");
		break;
	}
	errorOccurred(errorMessage);
}

void Panel::errorOccurred(QString error)
{
	QMessageBox messageBox(QMessageBox::Critical, tr("An error occurred"), error, QMessageBox::Ok, this);
	messageBox.exec();
}
