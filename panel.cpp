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
    on_textMessageField_textChanged();
	show();
	
	mClient->moveToThread(mClientThread);
	QObject::connect(this, &Panel::applyRequested, mClient, &Client::apply);
	QObject::connect(this, &Panel::restoreRequested, mClient, &Client::restore);
	QObject::connect(this, &Panel::hostnameChanged, mClient, &Client::setHostname);
	QObject::connect(this, &Panel::passwordChanged, mClient, &Client::setWorkingPassword);
	QObject::connect(mClient, &Client::done, this, &Panel::clientDone);
	QObject::connect(mClient, &Client::stateChanged, this, &Panel::clientStateChanged);

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
	applySettings();
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
	emit applyRequested();
}

void Panel::clientDone(Client::ClientError status)
{
	this->setEnabled(true);
	this->statusBar()->showMessage(tr("Ready"));
	if (status != Client::Ok)
		errorOccurred(status);
	// TODO: considerar especialmente el caso de contraseña incorrecta
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
	case Client::Timeout:
		errorMessage = tr("Connection timed out.");
		break;
	case Client::WrongResponse:
		errorMessage = tr("Received invalid response.");
		break;
	case Client::ConnectionRefused:
		errorMessage = tr("Connection refused by host.");
		break;
	case Client::RemoteHostClosed:
		errorMessage = tr("Remote host closed connection unexpectedly.");
		break;
	case Client::HostNotFound:
		errorMessage = tr("Host not found.");
		break;
	case Client::NetworkError:
		errorMessage = tr("Network error.");
		break;
	case Client::SslHandshakeFailed:
		errorMessage = tr("Received invalid response.");
		break;
	case Client::SslInternalError:
		errorMessage = tr("TLS internal error.");
		break;
	case Client::SslInvalidData:
		errorMessage = tr("Invalid TLS user data.");
		break;
	case Client::Unknown:
	default:
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

void Panel::clientStateChanged(Client::State state)
{
	QString text;
	switch (state) {
	case Client::NotReady:
		text = tr("Not ready.");
		break;
	case Client::Disconnected:
		text = tr("Ready.");
		break;
	case Client::Connecting:
		text = tr("Connecting to host...");
		break;
	case Client::Connected:
		text = tr("Connected.");
		break;
	case Client::RequestSent:
		text = tr("Waiting for response...");
		break;
	case Client::ResponseReceived:
		text = tr("ResponseReceived.");
		break;
	default:
		break;
	}

	this->statusBar()->showMessage(text);
}

void Panel::on_textMessageField_textChanged()
{
    ui->remainingChars->setText(QString::number(Message::TEXT_SIZE - ui->textMessageField->toPlainText().length()));
}
