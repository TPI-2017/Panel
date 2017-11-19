#include "panel.h"
#include "ui_panel.h"
#include "translation.h"
#include "logindialog.h"
#include "configdialog.h"
#include "passworddialog.h"
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
	validateText();
	setEnabled(false);
	show();

	// El objeto de tipo Client se ejecuta en otro hilo. Esto significa que
	// tiene su propia cola de eventos separada y todos sus slots se ejecutan
	// en paralelo a este hilo pero siempre un slot tras otro.
	mClient->moveToThread(mClientThread);
	// Widgets del panel
	connect(ui->aboutAction, &QAction::triggered,
		this, &Panel::showAboutDialog);
	connect(ui->quitAction, &QAction::triggered,
		this, &Panel::quit);
	connect(ui->changePasswordAction, &QAction::triggered,
		this, &Panel::showPasswordDialog);
	connect(ui->changeConfigAction, &QAction::triggered,
		this, &Panel::showConfigDialog);
	connect(ui->applyButton, &QPushButton::clicked,
		this, &Panel::applySettings);
	connect(ui->restoreButton, &QPushButton::clicked,
		this, &Panel::restoreSettings);

	// Para validar la longitud y codificación del texto
	// Estos connects son para cambios inmediatos en la GUI
	connect(ui->textMessageField,
		&QPlainTextEdit::textChanged,
		this,
		&Panel::validateText);
	connect(ui->slideCheckBox,
		QCheckBox::stateChanged,
		this,
		&Panel::slideRateCheckChanged);
	connect(ui->blinkCheckBox,
		QCheckBox::stateChanged,
		this,
		&Panel::blinkRateCheckChanged);

	connect(ui->speedSpinBox,
		static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
		this,
		&Panel::slideRateWidgetChanged);

	connect(ui->frequencySpinBox,
		static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
		this,
		&Panel::blinkRateWidgetChanged);


	// Para accionar un apply() o restore() en Client.
	connect(this, &Panel::applyRequested,
		mClient, &Client::apply);
	connect(this, &Panel::restoreRequested,
	mClient, &Client::restore);

	// Para setear el hostname y password en Client.
	connect(this, &Panel::hostnameChanged,
		mClient, &Client::setHostname);
	connect(this, &Panel::passwordChanged,
		mClient, &Client::setWorkingPassword);

	// Para que Client notifique a Panel sobre cambios o fin de operación.
	connect(mClient, &Client::done,
		this, &Panel::clientDone);
	connect(mClient, &Client::stateChanged,
		this, &Panel::updateState);

	// Para que el modelo actualice la vista
	connect(&mClient->model(), &SignModel::textChanged,
		ui->textMessageField, &QPlainTextEdit::setPlainText);
	connect(&mClient->model(), &SignModel::blinkRateChanged,
		this, &Panel::updateBlinkRate);
	connect(&mClient->model(), &SignModel::slideRateChanged,
		this, &Panel::updateSlideRate);

	// Para pasar cambios en la vista al controlador (Client)
	connect(this, &Panel::textChanged,
		mClient, &Client::setText);
	connect(this, &Panel::wifiConfigChanged,
		mClient, &Client::setWifiConfig);
	connect(this, &Panel::setPasswordIssued,
		mClient, &Client::setPassword);
	connect(this, &Panel::blinkRateChanged,
		mClient, &Client::setBlinkRate);
	connect(this, &Panel::slideRateChanged,
		mClient, &Client::setSlideRate);

	// Para pedir la reemisión de todos los valores del modelo
	connect(this, &Panel::modelEmitNeeded,
		&mClient->model(), &SignModel::emitValues);

	if (!showLoginPrompt()) {
		close();
		return;
	}

	mClientThread->start();

	// Traer los datos del servidor por primera vez
	restoreSettings();
}

// True si apretó OK, false si no.
bool Panel::showLoginPrompt()
{
	LoginDialog *loginDialog = new LoginDialog(this);
	int result = loginDialog->exec();

	if (result != QDialog::Accepted) {
		return false;
		delete loginDialog;
	}

	emit hostnameChanged(loginDialog->getHostname());
	emit passwordChanged(loginDialog->getPassword());

	delete loginDialog;
	return true;
}

void Panel::showAboutDialog()
{
	QMessageBox::information(this, tr("Authors"),
			    tr("\nLED Display - © 2017\n\n"
			    "García, Agustín\nLevy, Santiago\n"
			    "Romero Dapozo, Ramiro\nTernouski, Sebastian Nahuel\n"),
			    QMessageBox::Ok, 0);
}

void Panel::applySettings()
{
	this->setEnabled(false);
	emit textChanged(ui->textMessageField->toPlainText());
	emit blinkRateChanged(ui->frequencySpinBox->value());
	float slideRate = ui->speedSpinBox->value();
	if (ui->directionBox->currentIndex() == 0)
		slideRate *= -1.0;
	emit slideRateChanged(slideRate);
	emit applyRequested();
}

void Panel::restoreSettings()
{
	this->setEnabled(false);
	emit restoreRequested();
}

void Panel::showPasswordDialog()
{
	PasswordDialog *dialog = new PasswordDialog(this);
	if (dialog->exec() == QDialog::Accepted) {
		emit setPasswordIssued(dialog->getPassword());
		updateButtons(true);
	}
	delete dialog;
}

void Panel::updateText(QString text)
{
	ui->textMessageField->setPlainText(text);
}

void Panel::updateBlinkRate(float blinkRate)
{
	ui->blinkCheckBox->setCheckState(blinkRate ? Qt::Checked : Qt::Unchecked);
	ui->frequencySpinBox->setEnabled(blinkRate != 0);
	ui->frequencySpinBox->setValue(blinkRate);
}

void Panel::updateSlideRate(float slideRate)
{
	if (slideRate < 0) {
		slideRate = std::abs(slideRate);
		ui->directionBox->setCurrentIndex(0);
	} else {
		ui->directionBox->setCurrentIndex(1);
	}
	ui->slideCheckBox->setCheckState(slideRate ? Qt::Checked : Qt::Unchecked);
	ui->speedSpinBox->setEnabled(slideRate != 0);
	ui->directionBox->setEnabled(slideRate != 0);
	ui->speedSpinBox->setValue(slideRate);
}

void Panel::clientDone(Client::ClientError status)
{
	this->statusBar()->showMessage(tr("Ready"));
	if (status != Client::Ok) {
		showError(status);

		if (!showLoginPrompt()) {
			close();
			return;
		}
		restoreSettings();
	} else {
		updateButtons(false);
		this->setEnabled(true);
	}
}

void Panel::updateState(Client::State state)
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
		text = tr("Response received.");
		break;
	default:
		break;
	}

	this->statusBar()->showMessage(text);
}


void Panel::validateText()
{
	QString str = ui->textMessageField->toPlainText();
	if(str.length() > Message::TEXT_SIZE)
	{
		int diff = str.length() - Message::TEXT_SIZE;
		str.chop(diff);
		ui->textMessageField->setPlainText(str);
		QTextCursor cursor(ui->textMessageField->textCursor());
		cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
		ui->textMessageField->setTextCursor(cursor);
	}
	QString number = QString::number(Message::TEXT_SIZE - str.length());
	ui->remainingChars->setText(number);
	updateButtons(true);
}

void Panel::blinkRateCheckChanged(int state)
{
	bool checked = state == Qt::Checked;
	ui->frequencySpinBox->setEnabled(checked);
	if (!checked)
		ui->frequencySpinBox->setValue(0);
	updateButtons(true);
}

void Panel::slideRateCheckChanged(int state)
{
	bool checked = state == Qt::Checked;
	ui->speedSpinBox->setEnabled(checked);
	ui->directionBox->setEnabled(checked);
	if (!checked)
		ui->speedSpinBox->setValue(0);
	updateButtons(true);
}

void Panel::blinkRateWidgetChanged(double value)
{
	updateButtons(true);
}

void Panel::slideRateWidgetChanged(double value)
{
	updateButtons(true);
}

void Panel::updateButtons(bool pendingChanges)
{
	ui->applyButton->setEnabled(pendingChanges);
	ui->restoreButton->setEnabled(pendingChanges);
	mPendingChanges = pendingChanges;
}

void Panel::showConfigDialog()
{
	ConfigDialog *configDialog = new ConfigDialog(this);
	// Todas estas conexiones son para llenar el formulario
	connect(&mClient->model(),
		&SignModel::wifiSSIDChanged,
		configDialog,
		&ConfigDialog::setSSID);
	connect(&mClient->model(),
		&SignModel::wifiPasswordChanged,
		configDialog,
		&ConfigDialog::setPassword);
	connect(&mClient->model(),
		&SignModel::wifiIPChanged,
		configDialog,
		&ConfigDialog::setIP);
	connect(&mClient->model(),
		&SignModel::wifiSubnetMaskChanged,
		configDialog,
		&ConfigDialog::setMask);
	emit modelEmitNeeded();

	if (configDialog->exec() != QDialog::Accepted) {
		delete configDialog;
		return;
	}

	updateButtons(true);
	emit wifiConfigChanged(	configDialog->getSSID(),
				configDialog->getPassword(),
				configDialog->getIP(),
				configDialog->getMask());
	delete configDialog;
}

void Panel::showError(Client::ClientError error)
{
	QString errorMessage;
	switch (error) {
	case Client::CertificateMissing:
		errorMessage = tr("Failed to load TLS certificate.");
		break;
	case Client::Timeout:
		errorMessage = tr("Connection timed out.");
		break;
	case Client::WrongResponse:
		errorMessage = tr("Corrupt response.");
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
	case Client::ServerMalformedPacket:
		errorMessage = tr("Malformed packet.");
		break;
	case Client::ServerBadPassword:
		errorMessage = tr("Wrong password.");
		break;
	case Client::ServerBadProtocolVersion:
		errorMessage = tr("Protocol version mismatch.");
		break;
	case Client::ServerBadIP:
		errorMessage = tr("Invalid IP.");
		break;
	case Client::ServerBadSubnetMask:
		errorMessage = tr("Invalid IP subnet mask.");
		break;
	case Client::Unknown:
	default:
		errorMessage = tr("Unknown error.");
		break;
	}

	QMessageBox messageBox( QMessageBox::Critical,
				tr("An error occurred"),
				errorMessage,
				QMessageBox::Ok,
				this);
	messageBox.exec();
}

void Panel::quit()
{
	close();
}

Panel::~Panel()
{
	delete ui;
}

void Panel::closeEvent(QCloseEvent *event)
{
	int result = QMessageBox::Accepted;
	if (mPendingChanges) {
		result = QMessageBox::warning(this,
				tr("Panel"),
				tr("Quit without saving?"),
				QMessageBox::Ok | QMessageBox::Cancel);
	}

	if (result == QMessageBox::Accepted)
		event->accept();
	else
		event->ignore();
}
