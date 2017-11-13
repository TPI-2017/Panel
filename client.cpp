#include "client.h"
#include <stdint.h>
#include <QHostAddress>

Client::Client()
: mSocket(this)
{
	qRegisterMetaType<Client::State>("Client::State");
	qRegisterMetaType<Client::Error>("Client::Error");
}

void Client::init()
{
	changeState(NotReady);
	loadLocalCertificate();
}

void Client::loadLocalCertificate()
{
	QString path = ":/ssl/res/TLS.ca_x509.cer";

	auto list = QSslCertificate::fromPath(path, QSsl::Der);
	if (list.empty()) {
		changeState(NotReady);
		emit errorOccurred(Error::CertificateMissing);
		return;
	} else {
		mCertificate = list.front();
	}

	mSocket.addCaCertificate(mCertificate);
	changeState(Disconnected);
}

void Client::setHostname(QString hostname)
{
	mHostname = hostname;
}

void Client::setWorkingPassword(QString password)
{
	mPassword = password;
}

void Client::setText(QString text, uint8_t blinkRate, uint8_t slideRate)
{
	if (mState != Disconnected)
		return;

	mRequestMessage = Message::createSetTextRequest(blinkRate, slideRate, text.toStdString().data());
	performInteraction();
}

void Client::getText()
{
	if (mState != Disconnected)
		return;

	mRequestMessage = Message::createGetTextRequest();
	performInteraction();
}

void Client::setPassword(QString password)
{
	if (mState != Disconnected)
		return;

	mRequestMessage = Message::createSetPasswordRequest(password.toStdString().data());
}

void Client::setWifiConfig(QString SSID, QString wifiPassword, QHostAddress ip, QHostAddress subnetMask)
{
	if (mState != Disconnected)
		return;

	mRequestMessage = Message::createSetWifiConfigRequest(SSID.toStdString().data(), wifiPassword.toStdString().data(), ip.toIPv4Address(), subnetMask.toIPv4Address());
	performInteraction();
}

void Client::getWifiConfig()
{
	if (mState != Disconnected)
		return;

	mRequestMessage = Message::createGetWifiConfigRequest();
	performInteraction();
}

void Client::performInteraction()
{
	const Message authRequest = Message::createAuthRequest(mPassword.toStdString().data());
	char incomingBuffer[Message::MESSAGE_SIZE];
	
	// Abrimos conexión TLS
	mSocket.connectToHostEncrypted(mHostname, 443);
	changeState(Connecting);
	mSocket.waitForEncrypted(Timeout);
	if (!mSocket.isEncrypted()) {
		panic(mSocket.errorString());
		return;
	}
	changeState(Connected);
	
	// Nos autenticamos
	{
		qint64 bytesWritten;
		bytesWritten = mSocket.write(static_cast<const char*>(authRequest.data()), Message::MESSAGE_SIZE);
		if (bytesWritten != Message::MESSAGE_SIZE) {
			panic(IncompleteWrite);
			return;
		}
			
		changeState(AuthSent);
		if (!receive(incomingBuffer, Timeout)) {
			panic(ResponseTimeout);
			return;
		}
			
		Message authResponse = Message::createMessage(incomingBuffer);
		
		switch (authResponse.type())
		{
		case Message::OK:
			changeState(AuthOk); 
			break;
		default:
			break;
		}

		if (authResponse.type() != Message::Type::OK) {
			return;
		}
	}

	// Mandamos la solicitud
	{
		qint64 bytesWritten;
		bytesWritten = mSocket.write(static_cast<const char*>(authRequest.data()), Message::MESSAGE_SIZE);
		changeState(RequestSent);
		mSocket.waitForReadyRead(Timeout);
		receive(incomingBuffer, Timeout);
		mResponseMessage = Message::createMessage(incomingBuffer);

		switch(mRequestMessage.type())
		{
		case Message::SetText:
		case Message::SetWiFiConfig:
			if (mResponseMessage.type() != Message::OK) {
				panic(WrongResponse);
				return;
			}
			break;
		case Message::SetPassword:
			if (mResponseMessage.type() != Message::OK) {
				panic(WrongResponse);
				return;
			}
			// La próxima usamos la nueva contraseña
			mPassword = QString::fromLatin1(mRequestMessage.text());
			break;
		case Message::GetText:
			if (mResponseMessage.type() != Message::GetTextResponse) {
				panic(WrongResponse);
				return;
			}
			emit textChanged(QString::fromLatin1(mResponseMessage.text()));
			break;
		case Message::GetWiFiConfig:
			if (mResponseMessage.type() != Message::GetWiFiConfigResponse) {
				panic(WrongResponse);
				return;
			}
			emit wifiConfigChanged(	QString::fromLatin1(mResponseMessage.wifiSSID()),
						QString::fromLatin1(mResponseMessage.wifiPassword()),
						QHostAddress(mResponseMessage.wifiIP()),
						QHostAddress(mResponseMessage.wifiSubnet())
						);
			break;
		default:
			break;
		}
	}
	
	disconnect();
}

void Client::disconnect()
{
	if (mSocket.isOpen()) {
		mSocket.close();
	}
	changeState(Disconnected);
}

void Client::panic(Client::Error reason)
{
	emit errorOccurred(reason);
	disconnect();
}

void Client::panic(QString reason)
{
	emit errorOccurred(reason);
	disconnect();
}

bool Client::receive(void *data, uint16_t timeoutTime)
{
	if (mSocket.waitForReadyRead(timeoutTime)) {
		mSocket.read(static_cast<char*>(data), Message::MESSAGE_SIZE);
		return true;
	} else {
		return false;
	}
}

void Client::changeState(State newState)
{
	mState = newState;
	emit stateChanged(mState);
}
