#include "client.h"
#include <stdint.h>
#include <QHostAddress>

Client::Client()
: mState(State::NotReady)
{
	connect(&mSocket, &QSslSocket::encrypted, this, &Client::connected);
	connect(&mSocket, &QSslSocket::disconnected, this, &Client::disconnected);
	connect(&mSocket, &QSslSocket::readyRead, this, &Client::readyToRead);
	connect(&mSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(error(QAbstractSocket::SocketError)));
	connect(&mSocket, SIGNAL(sslErrors(QList<QSslError>)), this, SLOT(sslErrors(QList<QSslError>)));
	loadLocalCertificate();
}

void Client::loadLocalCertificate()
{
	QString path = ":/ssl/res/TLS.ca_x509.cer";

	auto list = QSslCertificate::fromPath(path, QSsl::Der);
	if (list.empty())
		emit errorOccurred(Error::CertificateMissing);
	else
		mCertificate = list.front();

	mSocket.addCaCertificate(mCertificate);
}

void Client::changeState(State newState)
{
	mState = newState;
	emit stateChanged(mState);
}

void Client::connected()
{
	changeState(Connected);
	// output->insertPlainText("Connected.\n");
}

void Client::disconnected()
{
	changeState(Disconnected);
	// output->insertPlainText("Disconnected.\n");
}

void Client::error(QAbstractSocket::SocketError err)
{
	// output->insertPlainText(socket->errorString() + "\n");
	changeState(Disconnected);
}

void Client::readyToRead()
{
	// QByteArray array(mSocket.readAll());
	// output->insertPlainText(QString::fromLatin1(array));
}

void Client::sslErrors(const QList<QSslError> &errors)
{
	for (const QSslError &err : errors)
	{
		// output->insertPlainText(err.errorString() + "\n");
	}
}

void Client::setText(QString text, uint8_t blinkRate, uint8_t slideRate)
{
    if (mState != Disconnected)
        return;
}

void Client::getText()
{
    if (mState != Disconnected)
        return;
}

void Client::setPassword(QString password)
{
    if (mState != Disconnected)
        return;
}

void Client::setWifiConfig(QString SSID, QString wifiPassword, QHostAddress ip, QHostAddress subnetMask)
{
    if (mState != Disconnected)
        return;
}

void Client::getWifiConfig()
{
    if (mState != Disconnected)
        return;
}
